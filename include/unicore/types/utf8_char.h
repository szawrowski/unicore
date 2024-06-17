// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF8_CHAR_H_
#define UNICORE_TYPES_UTF8_CHAR_H_

#include <cstdint>
#include <string>
#include <utility>

#include "unicore/types/basic_char.h"
#include "unicore/types/unicode_char.h"

namespace unicore {

template <>
class UnicodeChar<Utf8Char> {
public:
  using CharType = Utf8Char;
  using StringType = std::basic_string<CharType>;
  using CodepointType = uint32_t;
  using SizeType = size_t;

public:
  UnicodeChar() = default;

  UnicodeChar(const CodepointType codepoint) : codepoint_(codepoint){
    CalculateUtf8Length(codepoint);
  }

  UnicodeChar(const CharType* str) { FromBytes(str); }

public:
  UnicodeChar& operator=(const CodepointType codepoint) {
    codepoint_ = codepoint;
    CalculateUtf8Length(codepoint);
    return *this;
  }

  UnicodeChar& operator=(const CharType* str) {
    FromBytes(str);
    return *this;
  }

public:
  [[nodiscard]] CodepointType GetCodepoint() const { return codepoint_; }

  [[nodiscard]] SizeType ByteCount() const { return CalculateUtf8Length(codepoint_); }

  [[nodiscard]] std::string ToBytes() const {
    const auto length = CalculateUtf8Length(codepoint_);
    if (codepoint_ == 0) {
      return {};
    }
    std::string buffer(length, '\0');
    if (length == 1) {
      buffer[0] = static_cast<CharType>(codepoint_);
    } else if (length == 2) {
      buffer[0] = static_cast<CharType>(0xC0 | (codepoint_ >> 6));
      buffer[1] = static_cast<CharType>(0x80 | (codepoint_ & 0x3F));
    } else if (length == 3) {
      buffer[0] = static_cast<CharType>(0xE0 | (codepoint_ >> 12));
      buffer[1] = static_cast<CharType>(0x80 | ((codepoint_ >> 6) & 0x3F));
      buffer[2] = static_cast<CharType>(0x80 | (codepoint_ & 0x3F));
    } else {
      buffer[0] = static_cast<CharType>(0xF0 | (codepoint_ >> 18));
      buffer[1] = static_cast<CharType>(0x80 | ((codepoint_ >> 12) & 0x3F));
      buffer[2] = static_cast<CharType>(0x80 | ((codepoint_ >> 6) & 0x3F));
      buffer[3] = static_cast<CharType>(0x80 | (codepoint_ & 0x3F));
    }
    return buffer;
  }

  [[nodiscard]] std::pair<char16_t, char16_t> ToU16Char() const {
    if (codepoint_ <= 0xFFFF) {
      return std::make_pair(static_cast<char16_t>(codepoint_), char16_t{0});
    }
    const CodepointType codepoint = codepoint_ - 0x10000;
    auto high_surrogate = static_cast<char16_t>((codepoint >> 10) + 0xD800);
    auto low_surrogate = static_cast<char16_t>((codepoint & 0x3FF) + 0xDC00);
    return {high_surrogate, low_surrogate};
  }

  [[nodiscard]] char32_t ToU32Char() const { return codepoint_; }

private:
  static size_t CalculateUtf8Length(const CodepointType codepoint) {
    if (codepoint < 0x80) {
      return 1;
    }
    if (codepoint < 0x800) {
      return 2;
    }
    if (codepoint < 0x10000) {
      return 3;
    }
    return 4;
  }

  void FromBytes(const StringType& str) {
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
  CodepointType codepoint_{};
};

using U8Char = UnicodeChar<Utf8Char>;

}  // namespace unicore

static unicore::U8Char ReadU8Char(std::istream& is) {
  if (!is.good()) {
    return {};
  }
  char buffer[4] = {};
  is.read(buffer, 1);

  size_t length = 0;
  if ((buffer[0] & 0x80) == 0) {
    length = 1;
  } else if ((buffer[0] & 0xE0) == 0xC0) {
    length = 2;
  } else if ((buffer[0] & 0xF0) == 0xE0) {
    length = 3;
  } else if ((buffer[0] & 0xF8) == 0xF0) {
    length = 4;
  }
  if (length > 1) {
    is.read(buffer + 1, static_cast<std::streamsize>(length - 1));
  }
  return buffer;
}

static bool operator==(const unicore::U8Char lhs, const unicore::U8Char rhs) {
  const auto is_equal = lhs.GetCodepoint() == rhs.GetCodepoint();
  return is_equal;
}

static bool operator!=(const unicore::U8Char lhs, const unicore::U8Char rhs) {
  return !(lhs == rhs);
}

static std::istream& operator>>(std::istream& is, unicore::U8Char& c) {
  if (is.good()) {
    c = ReadU8Char(is);
  }
  return is;
}

static std::ostream& operator<<(std::ostream& os, const unicore::U8Char& c) {
  if (os.good()) {
    os.write(c.ToBytes().c_str(), static_cast<std::streamsize>(c.ByteCount()));
  }
  return os;
}

#endif  // UNICORE_TYPES_UTF8_CHAR_H_
