// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF32_STRING_H_
#define UNICORE_TYPES_UTF32_STRING_H_

#include <string>
#include <vector>

#include "unicore/iterators/unicode_string_const_iterator.h"
#include "unicore/iterators/unicode_string_iterator.h"
#include "unicore/types/char/utf32_char.h"
#include "unicore/types/string/unicode_string.h"
#include "unicore/utility/string_converter.h"

namespace uni {

template <>
class UnicodeString<U32Char> {
public:
  using CharType = U32Char;
  using BasicCharType = U32Char::CharType;
  using StringType = std::basic_string<BasicCharType>;
  using SizeType = size_t;
  using Iterator = UnicodeStringIterator<U32Char>;
  using ConstIterator = UnicodeStringConstIterator<U32Char>;
  using DataType = std::vector<CharType>;
  using CodepointType = uint32_t;

public:
  UnicodeString() = default;

  UnicodeString(const BasicCharType* str) { FromChars(str); }

  UnicodeString(const StringType& str) { FromChars(str); }

  UnicodeString(const UnicodeString& other) : data_{other.data_} {}

  UnicodeString(UnicodeString&& other) : data_{std::move(other.data_)} {}

public:
  UnicodeString& operator=(const StringType& str) {
    FromChars(str);
    return *this;
  }

  UnicodeString& operator=(const BasicCharType* str) {
    FromChars(StringType{str});
    return *this;
  }

  UnicodeString& operator=(const UnicodeString& other) = default;

  UnicodeString& operator=(UnicodeString&& other) noexcept {
    this->data_ = std::move(other.data_);
    return *this;
  }

public:
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

public:
  void Append(const CharType& value) { data_.push_back(value); }

  void Append(const UnicodeString& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
  }

public:
  [[nodiscard]] std::basic_string<Utf8Char> ToStdString() const {
    std::basic_ostringstream<Utf8Char> oss;
    for (const auto& c : data_) {
      oss << ConvertToStdString(c.GetCodepoint());
    }
    return oss.str();
  }

  [[nodiscard]] std::basic_string<Utf16Char> ToU16String() const {
    std::basic_ostringstream<Utf16Char> oss;
    for (const auto c : data_) {
      oss << ConvertToStdU16String(c.GetCodepoint());
    }
    return oss.str();
  }

  [[nodiscard]] std::basic_string<Utf32Char> ToU32String() const {
    std::basic_ostringstream<Utf32Char> oss;
    for (const auto& c : data_) {
      oss << ConvertToStdU32String(c.GetCodepoint());
    }
    return oss.str();
  }

public:
  [[nodiscard]] SizeType CharCount() const { return data_.size(); }

  [[nodiscard]] SizeType ByteCount() const {
    return data_.size() * sizeof(BasicCharType) * 4;
  }

public:
  [[nodiscard]] SizeType Size() const { return data_.size(); }

  [[nodiscard]] SizeType Length() const { return data_.size(); }

  [[nodiscard]] bool IsEmpty() const { return data_.empty(); }

  void PushBack(const CharType& c) { data_.push_back(c); }

  void PopBack() { data_.pop_back(); }

  void Clear() { data_.clear(); }

private:
  void FromChars(const StringType& str) {
    for (const auto& ch : str) {
      data_.emplace_back(ch);
    }
  }

private:
  DataType data_;
};

using U32String = UnicodeString<U32Char>;

}  // namespace uni

#endif  // UNICORE_TYPES_UTF32_STRING_H_
