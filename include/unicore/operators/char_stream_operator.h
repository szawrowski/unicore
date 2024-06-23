// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_CHAR_STREAM_OPERATOR_H_
#define UNICORE_OPERATORS_CHAR_STREAM_OPERATOR_H_

#include "unicore/types/char/unicode_char.h"
#include "unicore/utility/char_utility.h"
#include "unicore/utility/string_converter.h"

static std::basic_istream<uni::u8char_t>& operator>>(
    std::basic_istream<uni::u8char_t>& is, uni::char_t& c) {
  if (is.good()) {
    c = uni::impl::read_u8char(is);
  }
  return is;
}

static std::basic_ostream<uni::u8char_t>& operator<<(
    std::basic_ostream<uni::u8char_t>& os, const uni::char_t& c) {
  if (os.good()) {
    os << uni::impl::char_to_std_string<uni::u8char_t>(c.get_codepoint());
  }
  return os;
}

#endif  // UNICORE_OPERATORS_CHAR_STREAM_OPERATOR_H_
