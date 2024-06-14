// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_U8STRING_H_
#define UNICORE_TYPES_U8STRING_H_

#include <string>
#include <vector>

#include "unicore/types/u8char.h"

namespace unicore {

class U8String {
public:
  U8String() {}

  U8String(const std::string& str) { FromBytes(str); }

  U8String(const char* str) { FromBytes(std::string{str}); }

  U8String& operator=(const std::string& str) {
    FromBytes(str);
    return *this;
  }

  U8String& operator=(const char* str) {
    FromBytes(std::string{str});
    return *this;
  }

  class Iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = U8Char;
    using difference_type = std::ptrdiff_t;
    using pointer = U8Char*;
    using reference = U8Char&;

    Iterator(std::vector<U8Char>::iterator it) : it_(it) {}

    U8Char& operator*() const { return *it_; }

    Iterator& operator++() {
      ++it_;
      return *this;
    }

    Iterator operator++(int) {
      const Iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const Iterator& rhs) const { return it_ == rhs.it_; }

    bool operator!=(const Iterator& rhs) const { return !(*this == rhs); }

  private:
    std::vector<U8Char>::iterator it_;
  };

  class ConstIterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = const U8Char;
    using difference_type = std::ptrdiff_t;
    using pointer = const U8Char*;
    using reference = const U8Char&;

    ConstIterator(const std::vector<U8Char>::const_iterator it) : it_(it) {}

    const U8Char& operator*() const { return *it_; }

    ConstIterator& operator++() {
      ++it_;
      return *this;
    }

    ConstIterator operator++(int) {
      const ConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const ConstIterator& rhs) const { return it_ == rhs.it_; }

    bool operator!=(const ConstIterator& rhs) const { return !(*this == rhs); }

  private:
    std::vector<U8Char>::const_iterator it_;
  };

  [[nodiscard]] std::string ToBytes() const {
    std::string result;
    for (const auto& c : chars_) {
      result += c.ToBytes();
    }
    return result;
  }

  void Append(const U8Char& utf8_char) { chars_.push_back(utf8_char); }

  void Append(const U8String& other) {
    chars_.insert(chars_.end(), other.chars_.begin(), other.chars_.end());
  }

  [[nodiscard]] std::u16string ToU16String() const {
    std::u16string result;
    for (const auto& c : chars_) {
      auto [first, secind] = c.ToU16Char();
      result.push_back(first);
      if (secind != 0) {
        result.push_back(secind);
      }
    }
    return result;
  }

  [[nodiscard]] std::u32string ToU32String() const {
    std::u32string result;
    for (const auto& c : chars_) {
      auto [first, second, third, fourth] = c.ToU32Char();
      result.push_back(first);
      if (second != 0) {
        result.push_back(second);
      }
      if (third != 0) {
        result.push_back(third);
      }
      if (fourth != 0) {
        result.push_back(fourth);
      }
    }
    return result;
  }

  [[nodiscard]] size_t CharCount() const { return chars_.size(); }

  [[nodiscard]] size_t ByteCount() const {
    size_t byte_count = 0;
    for (const auto& c : chars_) {
      byte_count += c.ByteCount();
    }
    return byte_count;
  }

  Iterator begin() { return Iterator{chars_.begin()}; }
  Iterator end() { return Iterator{chars_.end()}; }

  [[nodiscard]] ConstIterator begin() const {
    return ConstIterator{chars_.begin()};
  }

  [[nodiscard]] ConstIterator end() const {
    return ConstIterator{chars_.end()};
  }

private:
  void FromBytes(const std::string& str) {
    size_t i = 0;
    while (i < str.length()) {
      U8Char c(str.c_str() + i);
      chars_.push_back(c);
      i += c.ByteCount();
    }
  }

  std::vector<U8Char> chars_;
};

}  // namespace unicore

#define UString(str) unicore::U8String{str}

static std::istream& operator>>(std::istream& is, unicore::U8String& str) {
  if (is.good()) {
    std::string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static std::ostream& operator<<(std::ostream& os,
                                const unicore::U8String& str) {
  if (os.good()) {
    os.write(str.ToBytes().c_str(),
             static_cast<std::streamsize>(str.ByteCount()));
  }
  return os;
}

#endif  // UNICORE_TYPES_U8STRING_H_
