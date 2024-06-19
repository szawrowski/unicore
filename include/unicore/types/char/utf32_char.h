// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF32_CHAR_H_
#define UNICORE_TYPES_UTF32_CHAR_H_

#include <cstdint>
#include <string>
#include <tuple>
#include <utility>

#include "unicore/types/char/basic_char.h"
#include "unicore/types/char/unicode_char.h"
#include "unicore/utility/length_calculation.h"

namespace unicore {

template <>
class UnicodeChar<Utf32Char> {
public:
  using CharType = Utf32Char;
  using StringType = std::basic_string<CharType>;
  using CodepointType = uint32_t;
  using SizeType = size_t;

public:
  UnicodeChar() = default;

  UnicodeChar(const CharType* symbol)
      : codepoint_{static_cast<CodepointType>(symbol[0])} {}

  UnicodeChar(const StringType& symbol)
      : codepoint_{static_cast<CodepointType>(symbol[0])} {}

  UnicodeChar(const CodepointType codepoint) : codepoint_{codepoint} {}

public:
  UnicodeChar& operator=(const CharType* str) {
    codepoint_ = static_cast<CodepointType>(str[0]);
    return *this;
  }

  UnicodeChar& operator=(const StringType& str) {
    codepoint_ = static_cast<CodepointType>(str[0]);
    return *this;
  }

  UnicodeChar& operator=(const CodepointType codepoint) {
    codepoint_ = codepoint;
    return *this;
  }

public:
  [[nodiscard]] CodepointType GetCodepoint() const { return codepoint_; }

private:
  CodepointType codepoint_{};
};

using U32Char = UnicodeChar<Utf32Char>;

}  // namespace unicore

#endif  // UNICORE_TYPES_UTF32_CHAR_H_
