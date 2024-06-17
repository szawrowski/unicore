#ifndef UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_

#include "unicore/types/utf8_char.h"

static bool operator==(const unicore::Char lhs, const unicore::Char rhs) {
  const auto is_equal = lhs.GetCodepoint() == rhs.GetCodepoint();
  return is_equal;
}

static bool operator!=(const unicore::Char lhs, const unicore::Char rhs) {
  return !(lhs == rhs);
}

#endif  // UNICORE_OPERATORS_UTF8_CHAR_COMPARISON_OPERATOR_H_
