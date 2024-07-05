// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_STRING_STREAM_OPERATOR_H_
#define UNICORE_OPERATORS_STRING_STREAM_OPERATOR_H_

#include "unicore/types/string/utf8_string.h"

static std::basic_istream<cait::u8char_t>& operator>>(
    std::basic_istream<cait::u8char_t>& is, cait::string& str) {
  if (is.good()) {
    std::string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static std::basic_ostream<cait::u8char_t>& operator<<(
    std::basic_ostream<cait::u8char_t>& os, const cait::string& str) {
  if (os.good()) {
    os << str.to_std_string();
  }
  return os;
}

#endif  // UNICORE_OPERATORS_STRING_STREAM_OPERATOR_H_
