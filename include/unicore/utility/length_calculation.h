// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_UTILITY_LENGTH_CALCULATION_H_
#define UNICORE_UTILITY_LENGTH_CALCULATION_H_

#include <cstddef>
#include <cstdint>

#include "unicore/defs/basic_char.h"

namespace uni {
namespace impl {

template <typename CharT>
static size_t calculate_sequence_length(uint32_t codepoint);

template <>
size_t calculate_sequence_length<u8char_t>(const uint32_t codepoint) {
  if (codepoint < 0x80) {
    return 1;
  }
  if (codepoint < 0x800) {
    return 2;
  }
  if (codepoint < 0x10000) {
    return 3;
  }
  return 4;
}

template <>
size_t calculate_sequence_length<u16char_t>(const uint32_t codepoint) {
  if (codepoint <= 0xFFFF) {
    return 1;
  }
  return 2;
}

}  // namespace impl
}  // namespace uni

#endif  // UNICORE_UTILITY_LENGTH_CALCULATION_H_
