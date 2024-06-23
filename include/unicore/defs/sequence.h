// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_DEFS_SEQUENCE_TYPE_H_
#define UNICORE_DEFS_SEQUENCE_TYPE_H_

#include "unicore/defs/basic_char.h"

namespace uni {

template <typename CharT>
class sequence_t;

template <>
class sequence_t<u8char_t> {
public:
  using type = std::tuple<u8char_t, u8char_t, u8char_t, u8char_t>;
};

template <>
class sequence_t<u16char_t> {
public:
  using type = std::tuple<u16char_t, u16char_t>;
};

}  // namespace uni

#endif  // UNICORE_DEFS_SEQUENCE_TYPE_H_
