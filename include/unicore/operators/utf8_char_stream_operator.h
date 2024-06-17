#ifndef UNICORE_OPERATORS_UTF8_CHAR_STREAM_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_CHAR_STREAM_OPERATOR_H_

#include "unicore/utility/char_utility.h"

static std::istream& operator>>(std::istream& is, unicore::Char& c) {
  if (is.good()) {
    c = unicore::impl::ReadChar(is);
  }
  return is;
}

static std::ostream& operator<<(std::ostream& os, const unicore::Char& c) {
  if (os.good()) {
    os.write(c.ToBytes().c_str(), static_cast<std::streamsize>(c.ByteCount()));
  }
  return os;
}

#endif  // UNICORE_OPERATORS_UTF8_CHAR_STREAM_OPERATOR_H_
