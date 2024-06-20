// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_

#include "unicore/types/char/utf16_char.h"
#include "unicore/types/char/utf32_char.h"
#include "unicore/types/char/utf8_char.h"

static bool operator==(const uni::Char lhs, const uni::Char rhs) {
  const auto is_equal = lhs.GetCodepoint() == rhs.GetCodepoint();
  return is_equal;
}

static bool operator!=(const uni::Char lhs, const uni::Char rhs) {
  return !(lhs == rhs);
}

static bool operator==(const uni::U16Char lhs, const uni::U16Char rhs) {
  const auto is_equal = lhs.GetCodepoint() == rhs.GetCodepoint();
  return is_equal;
}

static bool operator!=(const uni::U16Char lhs, const uni::U16Char rhs) {
  return !(lhs == rhs);
}

static bool operator==(const uni::U32Char lhs, const uni::U32Char rhs) {
  const auto is_equal = lhs.GetCodepoint() == rhs.GetCodepoint();
  return is_equal;
}

static bool operator!=(const uni::U32Char lhs, const uni::U32Char rhs) {
  return !(lhs == rhs);
}

#endif  // UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_
