// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_

#include "unicore/types/char/utf16_char.h"
#include "unicore/types/char/utf32_char.h"
#include "unicore/types/char/utf8_char.h"

static bool operator==(const unicore::Char lhs, const unicore::Char rhs) {
  const auto is_equal = lhs.GetCodepoint() == rhs.GetCodepoint();
  return is_equal;
}

static bool operator!=(const unicore::Char lhs, const unicore::Char rhs) {
  return !(lhs == rhs);
}

static bool operator==(const unicore::U16Char lhs, const unicore::U16Char rhs) {
  const auto is_equal = lhs.GetCodepoint() == rhs.GetCodepoint();
  return is_equal;
}

static bool operator!=(const unicore::U16Char lhs, const unicore::U16Char rhs) {
  return !(lhs == rhs);
}

static bool operator==(const unicore::U32Char lhs, const unicore::U32Char rhs) {
  const auto is_equal = lhs.GetCodepoint() == rhs.GetCodepoint();
  return is_equal;
}

static bool operator!=(const unicore::U32Char lhs, const unicore::U32Char rhs) {
  return !(lhs == rhs);
}

#endif  // UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_
