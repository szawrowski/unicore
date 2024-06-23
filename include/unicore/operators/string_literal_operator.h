// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_STRING_LITERAL_OPERATOR_H
#define UNICORE_OPERATORS_STRING_LITERAL_OPERATOR_H

#include "unicore/types/file/utf8_file.h"
#include "unicore/types/string/utf8_string.h"

static uni::string operator""_str(const uni::u8char_t* str,
                                  const std::size_t len) {
  return uni::string{str};
}

static uni::char_t operator""_char(const uni::u8char_t* symbol,
                                   const std::size_t len) {
  return uni::char_t{symbol};
}

static uni::file operator""_file(const uni::u8char_t* str,
                                 const std::size_t len) {
  return uni::file{str};
}

#endif  // UNICORE_OPERATORS_STRING_LITERAL_OPERATOR_H
