#ifndef UNICORE_OPERATORS_UTF8_STRING_COMPARISON_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_STRING_COMPARISON_OPERATOR_H_

#include "unicore/operators/utf8_char_comparison_operator.h"
#include "unicore/types/utf8_string.h"

static bool operator==(const unicore::String& lhs, const unicore::String& rhs) {
  for (auto lhs_it = lhs.begin(), lhs_end = lhs.end(), rhs_it = rhs.begin(),
            rhs_end = rhs.end();
       lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it) {
      return {};
    }
       }
  return true;
}

static bool operator!=(const unicore::String& lhs, const unicore::String& rhs) {
  return !(lhs == rhs);
}

#endif // UNICORE_OPERATORS_UTF8_STRING_COMPARISON_OPERATOR_H_
