// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UNICODE_CHAR_H_
#define UNICORE_TYPES_UNICODE_CHAR_H_

#include "unicore/defs/basic_char.h"

namespace uni {

template <typename CharT>
class unicode_char;

using char_t = unicode_char<u8char_t>;

}  // namespace uni

#endif  // UNICORE_TYPES_UNICODE_CHAR_H_
