// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_OPERATORS_UTF8_STRING_COMPARISON_OPERATOR_H_
#define UNICORE_OPERATORS_UTF8_STRING_COMPARISON_OPERATOR_H_

#include "unicore/operators/char_comparison_operator.h"
#include "unicore/types/string/utf16_string.h"
#include "unicore/types/string/utf32_string.h"
#include "unicore/types/string/utf8_string.h"

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

static bool operator==(const unicore::U16String& lhs,
                       const unicore::U16String& rhs) {
  for (auto lhs_it = lhs.begin(), lhs_end = lhs.end(), rhs_it = rhs.begin(),
            rhs_end = rhs.end();
       lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it) {
      return {};
    }
  }
  return true;
}

static bool operator!=(const unicore::U16String& lhs,
                       const unicore::U16String& rhs) {
  return !(lhs == rhs);
}

static bool operator==(const unicore::U32String& lhs,
                       const unicore::U32String& rhs) {
  for (auto lhs_it = lhs.begin(), lhs_end = lhs.end(), rhs_it = rhs.begin(),
            rhs_end = rhs.end();
       lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it) {
      return {};
    }
  }
  return true;
}

static bool operator!=(const unicore::U32String& lhs,
                       const unicore::U32String& rhs) {
  return !(lhs == rhs);
}

#endif  // UNICORE_OPERATORS_UTF8_STRING_COMPARISON_OPERATOR_H_
