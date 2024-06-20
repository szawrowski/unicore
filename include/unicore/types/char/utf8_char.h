// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF8_CHAR_H_
#define UNICORE_TYPES_UTF8_CHAR_H_

#include <cstdint>
#include <string>
#include <tuple>
#include <utility>

#include "unicore/types/char/basic_char.h"
#include "unicore/types/char/unicode_char.h"
#include "unicore/utility/length_calculation.h"

namespace uni {

template <>
class UnicodeChar<Utf8Char> {
public:
  using CharType = Utf8Char;
  using StringType = std::basic_string<CharType>;
  using CodepointType = uint32_t;
  using SizeType = size_t;

public:
  UnicodeChar() = default;

  UnicodeChar(const CharType* symbol) { FromChars(symbol); }

  UnicodeChar(const StringType& symbol) { FromChars(symbol); }

  UnicodeChar(const CodepointType codepoint) : codepoint_{codepoint} {}

public:
  UnicodeChar& operator=(const CharType* str) {
    FromChars(str);
    return *this;
  }

  UnicodeChar& operator=(const StringType& str) {
    FromChars(str);
    return *this;
  }

  UnicodeChar& operator=(const CodepointType codepoint) {
    codepoint_ = codepoint;
    CalculateSequenceLength<CharType>(codepoint);
    return *this;
  }

public:
  [[nodiscard]] CodepointType GetCodepoint() const { return codepoint_; }

  [[nodiscard]] SizeType CharCount() const {
    return CalculateSequenceLength<CharType>(codepoint_);
  }

private:
  void FromChars(const StringType& str) {
    const auto lead = static_cast<unsigned char>(str[0]);
    if ((lead & 0x80) == 0) {
      codepoint_ = lead;
    } else if ((lead & 0xE0) == 0xC0) {
      codepoint_ = (lead & 0x1F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F);
    } else if ((lead & 0xF0) == 0xE0) {
      codepoint_ = (lead & 0x0F) << 12;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[2]) & 0x3F);
    } else if ((lead & 0xF8) == 0xF0) {
      codepoint_ = (lead & 0x07) << 18;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F) << 12;
      codepoint_ |= (static_cast<unsigned char>(str[2]) & 0x3F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[3]) & 0x3F);
    } else {
      codepoint_ = 0;
    }
  }

private:
  CodepointType codepoint_{};
};

using Char = UnicodeChar<Utf8Char>;

}  // namespace uni

#endif  // UNICORE_TYPES_UTF8_CHAR_H_
