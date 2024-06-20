// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_ITERATORS_UNICODE_STRING_ITERATOR_H_
#define UNICORE_ITERATORS_UNICODE_STRING_ITERATOR_H_

#include <iterator>
#include <vector>

namespace uni {

template <typename CharType>
class UnicodeStringIterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = CharType;
  using difference_type = std::ptrdiff_t;
  using pointer = CharType*;
  using reference = CharType&;

  UnicodeStringIterator(typename std::vector<CharType>::iterator it)
      : it_(std::move(it)) {}

  CharType& operator*() const { return *it_; }

  UnicodeStringIterator& operator++() {
    ++it_;
    return *this;
  }

  UnicodeStringIterator operator++(int) {
    UnicodeStringIterator temp = *this;
    ++(*this);
    return temp;
  }

  UnicodeStringIterator& operator--() {
    --it_;
    return *this;
  }

  UnicodeStringIterator operator--(int) {
    UnicodeStringIterator temp = *this;
    --(*this);
    return temp;
  }

  UnicodeStringIterator operator+(difference_type n) const { return {it_ + n}; }

  UnicodeStringIterator& operator+=(difference_type n) {
    it_ += n;
    return *this;
  }

  UnicodeStringIterator operator-(difference_type n) const { return {it_ - n}; }

  UnicodeStringIterator& operator-=(difference_type n) {
    it_ -= n;
    return *this;
  }

  difference_type operator-(const UnicodeStringIterator& rhs) const {
    return std::distance(rhs.it_, it_);
  }

  CharType& operator[](difference_type n) const { return *(it_ + n); }

  bool operator==(const UnicodeStringIterator& rhs) const {
    return it_ == rhs.it_;
  }
  bool operator!=(const UnicodeStringIterator& rhs) const {
    return !(*this == rhs);
  }

private:
  typename std::vector<CharType>::iterator it_;
};

}  // namespace uni

#endif  // UNICORE_ITERATORS_UNICODE_STRING_ITERATOR_H_
