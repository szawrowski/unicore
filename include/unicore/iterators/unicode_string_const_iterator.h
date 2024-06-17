// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_ITERATORS_UNICODE_STRING_CONST_ITERATOR_H_
#define UNICORE_ITERATORS_UNICODE_STRING_CONST_ITERATOR_H_

#include <iterator>
#include <vector>

namespace unicore {

template <typename CharType>
class UnicodeStringConstIterator {
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = const CharType;
  using difference_type = std::ptrdiff_t;
  using pointer = const CharType*;
  using reference = const CharType&;

  UnicodeStringConstIterator(typename std::vector<CharType>::const_iterator it)
      : it_(std::move(it)) {}

  const CharType& operator*() const { return *it_; }

  UnicodeStringConstIterator& operator++() {
    ++it_;
    return *this;
  }

  UnicodeStringConstIterator operator++(int) {
    UnicodeStringConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  UnicodeStringConstIterator& operator--() {
    --it_;
    return *this;
  }

  UnicodeStringConstIterator operator--(int) {
    UnicodeStringConstIterator temp = *this;
    --(*this);
    return temp;
  }

  UnicodeStringConstIterator operator+(difference_type n) const {
    return {it_ + n};
  }

  UnicodeStringConstIterator& operator+=(difference_type n) {
    it_ += n;
    return *this;
  }

  UnicodeStringConstIterator operator-(difference_type n) const {
    return {it_ - n};
  }

  UnicodeStringConstIterator& operator-=(difference_type n) {
    it_ -= n;
    return *this;
  }

  difference_type operator-(const UnicodeStringConstIterator& rhs) const {
    return std::distance(rhs.it_, it_);
  }

  const CharType& operator[](difference_type n) const { return *(it_ + n); }

  bool operator==(const UnicodeStringConstIterator& rhs) const {
    return it_ == rhs.it_;
  }
  bool operator!=(const UnicodeStringConstIterator& rhs) const {
    return !(*this == rhs);
  }

private:
  typename std::vector<CharType>::const_iterator it_;
};

}  // namespace unicore

#endif  // UNICORE_ITERATORS_UNICODE_STRING_CONST_ITERATOR_H_
