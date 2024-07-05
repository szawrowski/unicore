// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_UTILITY_CHAR_SEQUENCE_CONVERTER_H_
#define UNICORE_UTILITY_CHAR_SEQUENCE_CONVERTER_H_

#include <tuple>

#include "unicore/defs/sequence.h"

namespace cait {
namespace impl {

template <typename CharT>
static typename sequence_t<CharT>::type get_sequence(uint32_t codepoint);

template <>
sequence_t<u8char_t>::type get_sequence<u8char_t>(const uint32_t codepoint) {
  const auto length = calculate_sequence_length<u8char_t>(codepoint);
  if (codepoint == 0) {
    return {};
  }
  if (length == 1) {
    return std::make_tuple(static_cast<u8char_t>(codepoint), 0x0, 0x0, 0x0);
  } else if (length == 2) {
    return std::make_tuple(static_cast<u8char_t>(0xC0 | (codepoint >> 6)),
                           static_cast<u8char_t>(0x80 | (codepoint & 0x3F)),
                           0x0, 0x0);
  } else if (length == 3) {
    return std::make_tuple(
        static_cast<u8char_t>(0xE0 | (codepoint >> 12)),
        static_cast<u8char_t>(0x80 | ((codepoint >> 6) & 0x3F)),
        static_cast<u8char_t>(0x80 | (codepoint & 0x3F)), 0x0);
  } else {
    return std::make_tuple(
        static_cast<u8char_t>(0xF0 | (codepoint >> 18)),
        static_cast<u8char_t>(0x80 | ((codepoint >> 12) & 0x3F)),
        static_cast<u8char_t>(0x80 | ((codepoint >> 6) & 0x3F)),
        static_cast<u8char_t>(0x80 | (codepoint & 0x3F)));
  }
}

template <>
sequence_t<u16char_t>::type get_sequence<u16char_t>(const uint32_t codepoint) {
  if (codepoint <= 0xFFFF) {
    return std::make_tuple(static_cast<u16char_t>(codepoint), 0x0);
  }
  const size_t current = codepoint - 0x10000;
  auto high = static_cast<u16char_t>((current >> 10) + 0xD800);
  auto low = static_cast<u16char_t>((current & 0x3FF) + 0xDC00);
  return std::make_tuple(high, low);
}

}  // namespace impl
}  // namespace cait

#endif  // UNICORE_UTILITY_CHAR_SEQUENCE_CONVERTER_H_
