// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_U8CHAR_H_
#define UNICORE_TYPES_U8CHAR_H_

#include <cstdint>
#include <string>
#include <tuple>
#include <utility>

namespace unicore {

class U8Char {
public:
  U8Char() : codepoint_(0), length_(0) {}

  U8Char(const uint32_t codepoint) : codepoint_(codepoint) {
    CalculateLength();
  }

  U8Char(const char* str) { FromBytes(str); }

  [[nodiscard]] uint32_t GetCodepoint() const { return codepoint_; }

  [[nodiscard]] size_t ByteCount() const { return length_; }

  [[nodiscard]] std::string ToBytes() const {
    if (length_ == 0) {
      return {};
    }
    std::string buffer(length_, '\0');
    if (length_ == 1) {
      buffer[0] = static_cast<char>(codepoint_);
    } else if (length_ == 2) {
      buffer[0] = 0xC0 | (codepoint_ >> 6);
      buffer[1] = 0x80 | (codepoint_ & 0x3F);
    } else if (length_ == 3) {
      buffer[0] = 0xE0 | (codepoint_ >> 12);
      buffer[1] = 0x80 | ((codepoint_ >> 6) & 0x3F);
      buffer[2] = 0x80 | (codepoint_ & 0x3F);
    } else {
      buffer[0] = 0xF0 | (codepoint_ >> 18);
      buffer[1] = 0x80 | ((codepoint_ >> 12) & 0x3F);
      buffer[2] = 0x80 | ((codepoint_ >> 6) & 0x3F);
      buffer[3] = 0x80 | (codepoint_ & 0x3F);
    }
    return buffer;
  }

  [[nodiscard]] std::tuple<char16_t, char16_t> ToU16Char() const {
    if (codepoint_ <= 0xFFFF) {
      return {static_cast<char16_t>(codepoint_), 0};
    }
    const uint32_t codepoint = codepoint_ - 0x10000;
    auto high_surrogate = static_cast<char16_t>((codepoint >> 10) + 0xD800);
    auto low_surrogate = static_cast<char16_t>((codepoint & 0x3FF) + 0xDC00);
    return {high_surrogate, low_surrogate};
  }

  [[nodiscard]] std::tuple<char32_t, char32_t, char32_t, char32_t> ToU32Char()
      const {
    if (codepoint_ <= 0x7F) {
      return {codepoint_, 0, 0, 0};
    }
    if (codepoint_ <= 0x7FF) {
      uint32_t byte1 = (codepoint_ >> 6) | 0xC0;
      uint32_t byte2 = (codepoint_ & 0x3F) | 0x80;
      return {byte1, byte2, 0, 0};
    }
    if (codepoint_ <= 0xFFFF) {
      uint32_t byte1 = (codepoint_ >> 12) | 0xE0;
      uint32_t byte2 = ((codepoint_ >> 6) & 0x3F) | 0x80;
      uint32_t byte3 = (codepoint_ & 0x3F) | 0x80;
      return {byte1, byte2, byte3, 0};
    }
    uint32_t byte1 = (codepoint_ >> 18) | 0xF0;
    uint32_t byte2 = ((codepoint_ >> 12) & 0x3F) | 0x80;
    uint32_t byte3 = ((codepoint_ >> 6) & 0x3F) | 0x80;
    uint32_t byte4 = (codepoint_ & 0x3F) | 0x80;
    return {byte1, byte2, byte3, byte4};
  }

private:
  void CalculateLength() {
    if (codepoint_ < 0x80) {
      length_ = 1;
    } else if (codepoint_ < 0x800) {
      length_ = 2;
    } else if (codepoint_ < 0x10000) {
      length_ = 3;
    } else {
      length_ = 4;
    }
  }

  void FromBytes(const char* str) {
    const auto lead = static_cast<unsigned char>(str[0]);
    if ((lead & 0x80) == 0) {
      codepoint_ = lead;
      length_ = 1;
    } else if ((lead & 0xE0) == 0xC0) {
      codepoint_ = (lead & 0x1F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F);
      length_ = 2;
    } else if ((lead & 0xF0) == 0xE0) {
      codepoint_ = (lead & 0x0F) << 12;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[2]) & 0x3F);
      length_ = 3;
    } else if ((lead & 0xF8) == 0xF0) {
      codepoint_ = (lead & 0x07) << 18;
      codepoint_ |= (static_cast<unsigned char>(str[1]) & 0x3F) << 12;
      codepoint_ |= (static_cast<unsigned char>(str[2]) & 0x3F) << 6;
      codepoint_ |= (static_cast<unsigned char>(str[3]) & 0x3F);
      length_ = 4;
    } else {
      codepoint_ = 0;
      length_ = 0;
    }
  }

private:
  uint32_t codepoint_;
  size_t length_;
};

static U8Char ReadU8Char(std::istream& is) {
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

}  // namespace unicore

#define UChar(str) unicore::U8Char{str}

static std::istream& operator>>(std::istream& is, unicore::U8Char& c) {
  if (is.good()) {
    c = unicore::ReadU8Char(is);
  }
  return is;
}

static std::ostream& operator<<(std::ostream& os, const unicore::U8Char& c) {
  if (os.good()) {
    os.write(c.ToBytes().c_str(), static_cast<std::streamsize>(c.ByteCount()));
  }
  return os;
}

#endif  // UNICORE_TYPES_U8CHAR_H_
