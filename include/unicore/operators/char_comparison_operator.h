// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_CHAR_COMPARISON_OPERATOR_H_
#define UNICORE_OPERATORS_CHAR_COMPARISON_OPERATOR_H_

#include "unicore/types/char/utf8_char.h"

static bool operator==(const uni::char_t lhs, const uni::char_t rhs) {
  return lhs.get_codepoint() == rhs.get_codepoint();
}

static bool operator!=(const uni::char_t lhs, const uni::char_t rhs) {
  return !(lhs == rhs);
}

#endif  // UNICORE_OPERATORS_CHAR_COMPARISON_OPERATOR_H_
