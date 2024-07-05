// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF8_CHAR_H_
#define UNICORE_TYPES_UTF8_CHAR_H_

#include <string>

#include "unicore/defs/basic_char.h"
#include "unicore/defs/unicode_type.h"
#include "unicore/types/char/unicode_char.h"
#include "unicore/utility/length_calculation.h"

namespace cait {

template <>
class unicode_char<u8char_t> {
public:
  using char_type = u8char_t;
  using string_type = std::basic_string<char_type>;
  using codepoint_type = codepoint_t;
  using size_type = size_t;

public:
  unicode_char() = default;

  unicode_char(const char_type* symbol) { from_chars(symbol); }

  unicode_char(const string_type& symbol) { from_chars(symbol); }

  unicode_char(const codepoint_type codepoint) : codepoint_{codepoint} {}

public:
  unicode_char& operator=(const char_type* str) {
    from_chars(str);
    return *this;
  }

  unicode_char& operator=(const string_type& str) {
    from_chars(str);
    return *this;
  }

  unicode_char& operator=(const codepoint_type codepoint) {
    codepoint_ = codepoint;
    impl::calculate_sequence_length<char_type>(codepoint);
    return *this;
  }

public:
  [[nodiscard]] codepoint_type get_codepoint() const { return codepoint_; }

  [[nodiscard]] size_type char_count() const {
    return impl::calculate_sequence_length<char_type>(codepoint_);
  }

private:
  void from_chars(const string_type& str) {
    const auto lead = static_cast<unsigned char>(str[0]);
    if ((lead & 0x80) == 0) {
      codepoint_ = lead;
    } else if ((lead & 0xE0) == 0xC0) {
      codepoint_ = (lead & 0x1F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F);
    } else if ((lead & 0xF0) == 0xE0) {
      codepoint_ = (lead & 0x0F) << 12;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[2]) & 0x3F);
    } else if ((lead & 0xF8) == 0xF0) {
      codepoint_ = (lead & 0x07) << 18;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F) << 12;
      codepoint_ |= (static_cast<unsigned char>(str[2]) & 0x3F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[3]) & 0x3F);
    } else {
      codepoint_ = 0;
    }
  }

private:
  codepoint_type codepoint_{};
};

}  // namespace cait

#endif  // UNICORE_TYPES_UTF8_CHAR_H_
