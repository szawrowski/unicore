// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_UTILITY_CHAR_UTILITY_H_
#define UNICORE_UTILITY_CHAR_UTILITY_H_

#include <istream>

namespace cait {
namespace impl {

static char_t read_u8char(std::basic_istream<u8char_t>& is) {
  if (!is.good()) {
    return {};
  }
  u8char_t buffer[4] = {};
  is.read(reinterpret_cast<char*>(&buffer[0]), sizeof(u8char_t));

  size_t length = 0;
  if ((buffer[0] & 0x80) == 0) {
    length = 1;
  } else if ((buffer[0] & 0xE0) == 0xC0) {
    length = 2;
  } else if ((buffer[0] & 0xF0) == 0xE0) {
    length = 3;
  } else if ((buffer[0] & 0xF8) == 0xF0) {
    length = 4;
  }
  if (length > 1) {
    if (!is.good()) {
      return {};
    }
    is.read(buffer + 1, static_cast<std::streamsize>(length - 1));
  }
  return buffer;
}

}  // namespace impl
}  // namespace cait

#endif  // UNICORE_UTILITY_CHAR_UTILITY_H_
