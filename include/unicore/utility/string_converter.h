// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_UTILITY_STRING_CONVERTER_H_
#define UNICORE_UTILITY_STRING_CONVERTER_H_

#include <sstream>

#include "unicore/utility/char_sequence_converter.h"

namespace uni {
namespace impl {

template <typename CharT>
std::basic_string<CharT> char_to_std_string(uint32_t codepoint);

template <>
std::basic_string<u8char_t> char_to_std_string(uint32_t codepoint) {
  std::basic_ostringstream<u8char_t> oss;
  const auto [first, second, third, fourth] =
      impl::get_sequence<u8char_t>(codepoint);
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

template <>
std::basic_string<u16char_t> char_to_std_string(uint32_t codepoint) {
  std::basic_ostringstream<u16char_t> oss;
  const auto [first, second] = impl::get_sequence<u16char_t>(codepoint);
  oss << first;
  if (second != 0x0) {
    oss << second;
  }
  return oss.str();
}

template <>
std::basic_string<u32char_t> char_to_std_string(uint32_t codepoint) {
  return {static_cast<u32char_t>(codepoint)};
}

}  // namespace impl
}  // namespace uni

#endif  // UNICORE_UTILITY_STRING_CONVERTER_H_
