#ifndef UNICORE_OPERATORS_UTF8_STRING_STREAM_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_STRING_STREAM_OPERATOR_H_

#include "unicore/types/utf8_string.h"

static std::istream& operator>>(std::istream& is, unicore::String& str) {
  if (is.good()) {
    std::string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static std::ostream& operator<<(std::ostream& os, const unicore::String& str) {
  if (os.good()) {
    os.write(str.ToStdString().c_str(),
             static_cast<std::streamsize>(str.ByteCount()));
  }
  return os;
}

#endif // UNICORE_OPERATORS_UTF8_STRING_STREAM_OPERATOR_H_
