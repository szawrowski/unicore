// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_STRING_LITERAL_OPERATOR_H
#define UNICORE_OPERATORS_STRING_LITERAL_OPERATOR_H

#include "unicore/types/string/utf8_string.h"

static cait::string operator""_str(const cait::u8char_t* str,
                                   const std::size_t len) {
  return cait::string{str};
}

static cait::char_t operator""_char(const cait::u8char_t* symbol,
                                    const std::size_t len) {
  return cait::char_t{symbol};
}

#endif  // UNICORE_OPERATORS_STRING_LITERAL_OPERATOR_H
