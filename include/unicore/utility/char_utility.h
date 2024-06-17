#ifndef CHAR_UTILITY_H
#define CHAR_UTILITY_H

#include <istream>

#include "unicore/types/utf8_char.h"

namespace unicore {
namespace impl {

static Char ReadChar(std::istream& is) {
  if (!is.good()) {
    return {};
  }
  char buffer[4] = {};
  is.read(buffer, 1);

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
    is.read(buffer + 1, static_cast<std::streamsize>(length - 1));
  }
  return buffer;
}

}  // namespace impl
}  // namespace unicore

#endif  // CHAR_UTILITY_H
