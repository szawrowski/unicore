// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_UTILITY_STRING_CONVERTER_H_
#define UNICORE_UTILITY_STRING_CONVERTER_H_

#include <sstream>

#include "unicore/utility/char_sequence_converter.h"

namespace unicore {

[[nodiscard]] std::basic_string<Utf8Char> ConvertToStdString(
    const uint32_t codepoint) {
  std::basic_ostringstream<Utf8Char> oss;
  const auto [first, second, third, fourth] = GetStdCharSequence(codepoint);
  oss << first;
  if (second != 0x0) {
    oss << second;
  }
  if (third != 0x0) {
    oss << third;
  }
  if (fourth != 0x0) {
    oss << fourth;
  }
  return oss.str();
}

[[nodiscard]] std::basic_string<Utf16Char> ConvertToStdU16String(
    const uint32_t codepoint) {
  std::basic_ostringstream<Utf16Char> oss;
  const auto [first, second] = GetStdU16CharSequence(codepoint);
  oss << first;
  if (second != 0x0) {
    oss << second;
  }
  return oss.str();
}

[[nodiscard]] std::basic_string<Utf32Char> ConvertToStdU32String(
    const uint32_t codepoint) {
  return std::basic_string<Utf32Char>{static_cast<Utf32Char>(codepoint)};
}

}  // namespace unicore

#endif  // UNICORE_UTILITY_STRING_CONVERTER_H_
