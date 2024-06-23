// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF8_STRING_H_
#define UNICORE_TYPES_UTF8_STRING_H_

#include <string>
#include <vector>

#include "unicore/iterators/unicode_string_const_iterator.h"
#include "unicore/iterators/unicode_string_iterator.h"
#include "unicore/types/char/utf8_char.h"
#include "unicore/types/string/unicode_string.h"
#include "unicore/utility/string_converter.h"

namespace uni {

template <>
class unicode_string<char_t> {
public:
  using char_type = char_t;
  using basic_char_type = char_t::char_type;
  using basic_string_type = std::basic_string<basic_char_type>;
  using size_type = size_t;
  using data_type = std::vector<char_type>;
  using iterator = unicode_string_iterator<char_t>;
  using const_iterator = unicode_string_const_iterator<char_t>;

public:
  unicode_string() = default;

  unicode_string(const basic_char_type* str) { from_chars(str); }

  unicode_string(const basic_string_type& str) { from_chars(str); }

  unicode_string(const unicode_string& other) : data_{other.data_} {}

  unicode_string(unicode_string&& other) : data_{std::move(other.data_)} {}

public:
  unicode_string& operator=(const basic_string_type& str) {
    from_chars(str);
    return *this;
  }

  unicode_string& operator=(const basic_char_type* str) {
    from_chars(basic_string_type{str});
    return *this;
  }

  unicode_string& operator=(const unicode_string& other) = default;

  unicode_string& operator=(unicode_string&& other) noexcept {
    this->data_ = std::move(other.data_);
    return *this;
  }

public:
  [[nodiscard]] const char_type& operator[](const size_type pos) const {
    return data_[pos];
  }

  [[nodiscard]] char_type& operator[](const size_type pos) {
    return data_[pos];
  }

  unicode_string& operator+=(const char_type& c) {
    push_back(c);
    return *this;
  }

public:
  [[nodiscard]] iterator begin() { return {data_.begin()}; }

  [[nodiscard]] iterator end() { return {data_.end()}; }

  [[nodiscard]] const_iterator begin() const { return data_.begin(); }

  [[nodiscard]] const_iterator end() const { return data_.end(); }

  [[nodiscard]] const_iterator cbegin() const { return data_.cbegin(); }

  [[nodiscard]] const_iterator cend() const { return data_.cend(); }

public:
  void append(const char_type& value) { data_.push_back(value); }

  void append(const unicode_string& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
  }

public:
  [[nodiscard]] std::string to_std_string() const {
    std::basic_ostringstream<u8char_t> oss;
    for (const auto& c : data_) {
      oss << impl::char_to_std_string<u8char_t>(c.get_codepoint());
    }
    return oss.str();
  }

  [[nodiscard]] std::u16string to_std_u16string() const {
    std::basic_ostringstream<u16char_t> oss;
    for (const auto c : data_) {
      oss << impl::char_to_std_string<u16char_t>(c.get_codepoint());
    }
    return oss.str();
  }

  [[nodiscard]] std::u32string to_std_u32string() const {
    std::basic_ostringstream<u32char_t> oss;
    for (const auto& c : data_) {
      oss << impl::char_to_std_string<u32char_t>(c.get_codepoint());
    }
    return oss.str();
  }

public:
  [[nodiscard]] size_type char_count() const { return data_.size(); }

  [[nodiscard]] size_type byte_count() const {
    size_type byte_count{};
    for (const auto& c : data_) {
      byte_count += c.char_count();
    }
    return byte_count;
  }

public:
  [[nodiscard]] size_type size() const { return data_.size(); }

  [[nodiscard]] size_type length() const { return data_.size(); }

  [[nodiscard]] bool is_empty() const { return data_.empty(); }

  void push_back(const char_type& c) { data_.push_back(c); }

  void pop_back() { data_.pop_back(); }

  void clear() { data_.clear(); }

private:
  void from_chars(const basic_string_type& str) {
    const auto size = str.size();

    for (size_type pos = 0; pos < size;) {
      if (pos >= size) {
        break;
      }
      char_t temp = str.substr(pos).c_str();
      data_.push_back(temp);
      pos += temp.char_count();
    }
  }

private:
  data_type data_;
};

}  // namespace uni

#endif  // UNICORE_TYPES_UTF8_STRING_H_
