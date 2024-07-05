// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_ITERATORS_UNICODE_STRING_CONST_ITERATOR_H_
#define UNICORE_ITERATORS_UNICODE_STRING_CONST_ITERATOR_H_

#include <iterator>
#include <vector>

namespace cait {

template <typename CharT>
class unicode_string_const_iterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = const CharT;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;
  using iterator_data = typename std::vector<CharT>::const_iterator;

  unicode_string_const_iterator(iterator_data it)
      : it_(std::move(it)) {}

  reference operator*() const { return *it_; }

  unicode_string_const_iterator& operator++() {
    ++it_;
    return *this;
  }

  unicode_string_const_iterator operator++(int) {
    unicode_string_const_iterator temp = *this;
    ++(*this);
    return temp;
  }

  unicode_string_const_iterator& operator--() {
    --it_;
    return *this;
  }

  unicode_string_const_iterator operator--(int) {
    unicode_string_const_iterator temp = *this;
    --(*this);
    return temp;
  }

  unicode_string_const_iterator operator+(difference_type n) const {
    return {it_ + n};
  }

  unicode_string_const_iterator& operator+=(difference_type n) {
    it_ += n;
    return *this;
  }

  unicode_string_const_iterator operator-(difference_type n) const {
    return {it_ - n};
  }

  unicode_string_const_iterator& operator-=(difference_type n) {
    it_ -= n;
    return *this;
  }

  difference_type operator-(const unicode_string_const_iterator& rhs) const {
    return std::distance(rhs.it_, it_);
  }

  reference operator[](difference_type n) const { return *(it_ + n); }

  bool operator==(const unicode_string_const_iterator& rhs) const {
    return it_ == rhs.it_;
  }
  bool operator!=(const unicode_string_const_iterator& rhs) const {
    return !(*this == rhs);
  }

private:
  iterator_data it_;
};

}  // namespace cait

#endif  // UNICORE_ITERATORS_UNICODE_STRING_CONST_ITERATOR_H_
