// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_UTILITY_CHAR_UTILITY_H_
#define UNICORE_UTILITY_CHAR_UTILITY_H_

#include <istream>

#include "unicore/types/char/utf16_char.h"
#include "unicore/types/char/utf32_char.h"
#include "unicore/types/char/utf8_char.h"

namespace unicore {
namespace impl {

static Char ReadU8Char(std::basic_istream<unicore::Utf8Char>& is) {
  if (!is.good()) {
    return {};
  }
  Utf8Char buffer[4] = {};
  is.read(reinterpret_cast<char*>(&buffer[0]), sizeof(Utf8Char));

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

static U16Char ReadU16Char(std::basic_istream<unicore::Utf16Char>& is) {
  if (!is.good()) {
    return {};
  }
  Utf16Char buffer[2] = {};
  is.read(reinterpret_cast<Utf16Char*>(&buffer[0]), sizeof(U16Char));

  if ((buffer[0] & 0xFC00) == 0xD800) {
    if (!is.good()) {
      return {};
    }
    is.read(reinterpret_cast<Utf16Char*>(&buffer[1]), sizeof(U16Char));
    if ((buffer[1] & 0xFC00) != 0xDC00) {
      throw std::invalid_argument("Invalid surrogate pair");
    }
    return buffer;
  } else {
    return buffer;
  }
}

static U32Char ReadU32Char(std::basic_istream<unicore::Utf32Char>& is) {
  if (!is.good()) {
    return {};
  }
  Utf32Char buffer[1] = {};
  is.read(reinterpret_cast<Utf32Char*>(&buffer), sizeof(Utf32Char));

  return buffer;
}

}  // namespace impl
}  // namespace unicore

#endif  // UNICORE_UTILITY_CHAR_UTILITY_H_
