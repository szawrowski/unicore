// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_UTF8_CHAR_STREAM_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_CHAR_STREAM_OPERATOR_H_

#include "unicore/utility/char_utility.h"
#include "unicore/utility/string_converter.h"

static std::basic_istream<uni::Utf8Char>& operator>>(
    std::basic_istream<uni::Utf8Char>& is, uni::Char& c) {
  if (is.good()) {
    c = uni::impl::ReadU8Char(is);
  }
  return is;
}

static std::basic_ostream<uni::Utf8Char>& operator<<(
    std::basic_ostream<uni::Utf8Char>& os, const uni::Char& c) {
  if (os.good()) {
    os.write(uni::ConvertToStdString(c.GetCodepoint()).c_str(),
             static_cast<std::streamsize>(c.CharCount()));
  }
  return os;
}

static std::basic_istream<uni::Utf16Char>& operator>>(
    std::basic_istream<uni::Utf16Char>& is, uni::U16Char& c) {
  if (is.good()) {
    c = uni::impl::ReadU16Char(is);
  }
  return is;
}

static std::basic_ostream<uni::Utf8Char>& operator<<(
    std::basic_ostream<uni::Utf8Char>& os, const uni::U16Char& c) {
  if (os.good()) {
    os.write(uni::ConvertToStdString(c.GetCodepoint()).c_str(),
             static_cast<std::streamsize>(c.CharCount() * 2));
  }
  return os;
}

static std::basic_istream<uni::Utf32Char>& operator>>(
    std::basic_istream<uni::Utf32Char>& is, uni::U32Char& c) {
  if (is.good()) {
    c = uni::impl::ReadU32Char(is);
  }
  return is;
}

static std::basic_ostream<uni::Utf8Char>& operator<<(
    std::basic_ostream<uni::Utf8Char>& os, const uni::U32Char& c) {
  if (os.good()) {
    os.write(uni::ConvertToStdString(c.GetCodepoint()).c_str(),
             static_cast<std::streamsize>(4));
  }
  return os;
}

#endif  // UNICORE_OPERATORS_UTF8_CHAR_STREAM_OPERATOR_H_
