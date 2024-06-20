// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_UTILITY_CHAR_SEQUENCE_CONVERTER_H_
#define UNICORE_UTILITY_CHAR_SEQUENCE_CONVERTER_H_

#include <tuple>

#include "unicore/types/char/basic_char.h"

namespace uni {

using StdCharSequence = std::tuple<Utf8Char, Utf8Char, Utf8Char, Utf8Char>;
using StdU16CharSequence = std::tuple<Utf16Char, Utf16Char>;

static StdCharSequence GetStdCharSequence(const uint32_t codepoint) {
  const auto length = CalculateSequenceLength<Utf8Char>(codepoint);
  if (codepoint == 0) {
    return {};
  }
  if (length == 1) {
    return std::make_tuple(static_cast<Utf8Char>(codepoint), 0x0, 0x0, 0x0);
  } else if (length == 2) {
    return std::make_tuple(static_cast<Utf8Char>(0xC0 | (codepoint >> 6)),
                           static_cast<Utf8Char>(0x80 | (codepoint & 0x3F)),
                           0x0, 0x0);
  } else if (length == 3) {
    return std::make_tuple(
        static_cast<Utf8Char>(0xE0 | (codepoint >> 12)),
        static_cast<Utf8Char>(0x80 | ((codepoint >> 6) & 0x3F)),
        static_cast<Utf8Char>(0x80 | (codepoint & 0x3F)), 0x0);
  } else {
    return std::make_tuple(
        static_cast<Utf8Char>(0xF0 | (codepoint >> 18)),
        static_cast<Utf8Char>(0x80 | ((codepoint >> 12) & 0x3F)),
        static_cast<Utf8Char>(0x80 | ((codepoint >> 6) & 0x3F)),
        static_cast<Utf8Char>(0x80 | (codepoint & 0x3F)));
  }
}

static StdU16CharSequence GetStdU16CharSequence(const uint32_t codepoint) {
  if (codepoint <= 0xFFFF) {
    return std::make_tuple(static_cast<Utf16Char>(codepoint), 0x0);
  }
  const size_t current = codepoint - 0x10000;
  auto high = static_cast<Utf16Char>((current >> 10) + 0xD800);
  auto low = static_cast<Utf16Char>((current & 0x3FF) + 0xDC00);
  return std::make_tuple(high, low);
}

static Utf32Char GetStdU32Char(const uint32_t codepoint) { return codepoint; }

}  // namespace uni

#endif  // UNICORE_UTILITY_CHAR_SEQUENCE_CONVERTER_H_
