// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF16_CHAR_H_
#define UNICORE_TYPES_UTF16_CHAR_H_

#include <cstdint>
#include <string>
#include <tuple>
#include <utility>

#include "unicore/types/char/basic_char.h"
#include "unicore/types/char/unicode_char.h"
#include "unicore/utility/length_calculation.h"

namespace unicore {

template <>
class UnicodeChar<Utf16Char> {
public:
  using CharType = Utf16Char;
  using StringType = std::basic_string<CharType>;
  using CodepointType = uint32_t;
  using SizeType = size_t;

public:
  UnicodeChar() = default;

  UnicodeChar(const CharType* symbol) { FromChars(symbol); }

  UnicodeChar(const StringType& symbol) { FromChars(symbol); }

  UnicodeChar(const CodepointType codepoint) : codepoint_{codepoint} {}

public:
  UnicodeChar& operator=(const StringType& str) {
    FromChars(str);
    return *this;
  }

  UnicodeChar& operator=(const CharType* str) {
    FromChars(str);
    return *this;
  }

  UnicodeChar& operator=(const CodepointType codepoint) {
    codepoint_ = codepoint;
    return *this;
  }

public:
  [[nodiscard]] CodepointType GetCodepoint() const { return codepoint_; }

  [[nodiscard]] SizeType CharCount() const {
    return CalculateSequenceLength<CharType>(codepoint_);
  }

private:
  void FromChars(const StringType& str) {
    if (str.size() == 1) {
      codepoint_ = static_cast<CodepointType>(str[0]);
    } else if (str.size() == 2) {
      const auto high = static_cast<CodepointType>(str[0]);
      const auto low = static_cast<CodepointType>(str[1]);
      codepoint_ = ((high - 0xD800) << 10) + (low - 0xDC00) + 0x10000;
    } else {
      codepoint_ = 0;
    }
  }

private:
  CodepointType codepoint_{};
};

using U16Char = UnicodeChar<Utf16Char>;

}  // namespace unicore

#endif  // UNICORE_TYPES_UTF16_CHAR_H_