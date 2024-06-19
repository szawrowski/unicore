// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_UTF8_STRING_STREAM_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_STRING_STREAM_OPERATOR_H_

#include "unicore/types/string/utf16_string.h"
#include "unicore/types/string/utf32_string.h"
#include "unicore/types/string/utf8_string.h"

static std::basic_istream<unicore::Utf8Char>& operator>>(
    std::basic_istream<unicore::Utf8Char>& is, unicore::String& str) {
  if (is.good()) {
    std::string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static std::basic_ostream<unicore::Utf8Char>& operator<<(
    std::basic_ostream<unicore::Utf8Char>& os, const unicore::String& str) {
  if (os.good()) {
    os.write(str.ToStdString().c_str(),
             static_cast<std::streamsize>(str.ByteCount()));
  }
  return os;
}

static std::basic_istream<unicore::Utf16Char>& operator>>(
    std::basic_istream<unicore::Utf16Char>& is, unicore::U16String& str) {
  if (is.good()) {
    std::u16string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static std::basic_ostream<unicore::Utf8Char>& operator<<(
    std::basic_ostream<unicore::Utf8Char>& os, const unicore::U16String& str) {
  if (os.good()) {
    os.write(str.ToStdString().c_str(),
             static_cast<std::streamsize>(str.ByteCount()));
  }
  return os;
}

static std::basic_istream<unicore::Utf32Char>& operator>>(
    std::basic_istream<unicore::Utf32Char>& is, unicore::U32String& str) {
  if (is.good()) {
    std::u32string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static std::basic_ostream<unicore::Utf8Char>& operator<<(
    std::basic_ostream<unicore::Utf8Char>& os, const unicore::U32String& str) {
  if (os.good()) {
    os.write(str.ToStdString().c_str(),
             static_cast<std::streamsize>(str.ByteCount()));
  }
  return os;
}

#endif  // UNICORE_OPERATORS_UTF8_STRING_STREAM_OPERATOR_H_