// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF8_STRING_H_
#define UNICORE_TYPES_UTF8_STRING_H_

#include <string>
#include <vector>

#include "unicore/iterators/unicode_string_iterator.h"
#include "unicore/iterators/unicode_string_const_iterator.h"
#include "unicore/types/unicode_string.h"
#include "unicore/types/utf8_char.h"

namespace unicore {

template <>
class UnicodeString<U8Char> {
public:
  using CharType = U8Char;
  using BasicCharType = U8Char::CharType;
  using StringType = std::basic_string<BasicCharType>;
  using OutputStringStreamType = std::basic_ostringstream<BasicCharType>;
  using SizeType = size_t;
  using Iterator = UnicodeStringIterator<U8Char>;
  using ConstIterator = UnicodeStringConstIterator<U8Char>;

public:
  UnicodeString() = default;

  UnicodeString(const StringType& str) { FromBytes(str); }

  UnicodeString(const BasicCharType* str) { FromBytes(StringType{str}); }

  template <typename Container>
  UnicodeString(const Container& container)
      : data_(container.begin(), container.end()) {}

  template <typename Iterator>
  UnicodeString(Iterator first, Iterator last) : data_(first, last) {}

public:
  UnicodeString& operator=(const StringType& str) {
    FromBytes(str);
    return *this;
  }

  UnicodeString& operator=(const BasicCharType* str) {
    FromBytes(StringType{str});
    return *this;
  }

public:
  void Append(const CharType& value) { data_.push_back(value); }

  void Append(const UnicodeString& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
  }

  [[nodiscard]] StringType ToBytes() const {
    OutputStringStreamType oss;
    for (const auto& c : data_) {
      oss << c.ToBytes();
    }
    return oss.str();
  }

  [[nodiscard]] std::basic_string<Utf16Char> ToU16String() const {
    std::basic_ostringstream<Utf16Char> oss;
    for (const auto c : data_) {
      auto [first, second] = c.ToU16Char();
      oss << first;
      if (second != 0x0) {
        oss << second;
      }
    }
    return oss.str();
  }

  [[nodiscard]] std::basic_string<Utf32Char> ToU32String() const {
    std::basic_ostringstream<Utf32Char> oss;
    for (const auto& c : data_) {
      oss << c.ToU32Char();
    }
    return oss.str();
  }

  [[nodiscard]] SizeType CharCount() const { return data_.size(); }

  [[nodiscard]] SizeType ByteCount() const {
    SizeType byte_count{};
    for (const auto& c : data_) {
      byte_count += c.ByteCount();
    }
    return byte_count;
  }

public:
  [[nodiscard]] SizeType Size() const { return data_.size(); }

  [[nodiscard]] SizeType Length() const { return data_.size(); }

  [[nodiscard]] bool IsEmpty() const { return data_.empty(); }

  void PushBack(const CharType& c) { data_.push_back(c); }

  void PopBack() { data_.pop_back(); }

  void Clear() { data_.clear(); }

  [[nodiscard]] const CharType& operator[](const SizeType index) const {
    return data_[index];
  }

  [[nodiscard]] CharType& operator[](const SizeType index) {
    return data_[index];
  }

  UnicodeString& operator+=(const CharType& c) {
    PushBack(c);
    return *this;
  }

public:
  [[nodiscard]] Iterator begin() { return {data_.begin()}; }

  [[nodiscard]] Iterator end() { return {data_.end()}; }

  [[nodiscard]] ConstIterator begin() const { return data_.begin(); }

  [[nodiscard]] ConstIterator end() const { return data_.end(); }

  [[nodiscard]] ConstIterator cbegin() const { return data_.cbegin(); }

  [[nodiscard]] ConstIterator cend() const { return data_.cend(); }

private:
  void FromBytes(const StringType& str) {
    const auto size = str.size();

    for (SizeType pos = 0; pos < size;) {
      if (pos >= size) {
        break;
      }
      U8Char temp = str.substr(pos).c_str();
      data_.push_back(temp);
      pos += temp.ByteCount();
    }
  }

private:
  std::vector<U8Char> data_;
};

using String = UnicodeString<U8Char>;

}  // namespace unicore

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

static std::istream& operator>>(std::istream& is, unicore::String& str) {
  if (is.good()) {
    std::string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static std::ostream& operator<<(std::ostream& os, const unicore::String& str) {
  if (os.good()) {
    os.write(str.ToBytes().c_str(),
             static_cast<std::streamsize>(str.ByteCount()));
  }
  return os;
}

#endif  // UNICORE_TYPES_UTF8_STRING_H_
