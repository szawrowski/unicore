// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF8_FILE_H_
#define UNICORE_TYPES_UTF8_FILE_H_

#include <filesystem>
#include <fstream>
#include <utility>

#include "unicore/operators/string_stream_operator.h"
#include "unicore/types/file/unicode_file.h"
#include "unicore/types/string/utf8_string.h"

namespace unicore {

template <>
class UnicodeFile<Char> {
public:
  using CharType = Char::CharType;
  using StringType = std::basic_string<CharType>;
  using InputFileStream = std::basic_ifstream<CharType>;
  using OutputFileStream = std::basic_ofstream<CharType>;
  using OutputStringStream = std::basic_ostringstream<CharType>;

public:
  UnicodeFile(const String& filename) : filename_{filename} {}

  UnicodeFile(const UnicodeFile& other) : filename_{other.filename_} {}

  UnicodeFile(UnicodeFile&& other) noexcept
      : filename_{std::move(other.filename_)} {}

public:
  UnicodeFile& operator=(const UnicodeFile& other) {
    if (this != &other) {
      filename_ = other.filename_;
    }
    return *this;
  }

  UnicodeFile& operator=(UnicodeFile&& other) noexcept {
    if (this != &other) {
      filename_ = std::move(other.filename_);
    }
    return *this;
  }

public:
  void SetFilename(const String& filename) { filename_ = filename; }

  [[nodiscard]] bool Exists() const {
    return std::filesystem::exists(GetFilename());
  }

  [[nodiscard]] std::uintmax_t GetSize() const {
    return std::filesystem::file_size(GetFilename());
  }

  void CopyTo(const String& dest) const {
    std::filesystem::copy(GetFilename(), dest.ToStdString(),
                          std::filesystem::copy_options::overwrite_existing);
  }

  void MoveTo(const String& dest) {
    std::filesystem::rename(GetFilename(), dest.ToStdString());
    filename_ = dest;
  }

  void Write(const String& data) const {
    OutputFileStream file(GetFilename(), std::ios::out | std::ios::binary);
    if (!file) {
      throw std::ios_base::failure("Failed to open file for writing");
    }
    file << data;
  }

  void WriteLine(const String& data) const {
    OutputFileStream file(GetFilename(),
                          std::ios::out | std::ios::app | std::ios::binary);
    if (!file) {
      throw std::ios_base::failure("Failed to open file for appending");
    }
    file << data << '\n';
  }

  [[nodiscard]] String Read() const {
    const InputFileStream file(GetFilename(), std::ios::in | std::ios::binary);
    if (!file) {
      throw std::ios_base::failure("Failed to open file for reading");
    }
    OutputStringStream oss;
    oss << file.rdbuf();
    return oss.str();
  }

  [[nodiscard]] String ReadLine() const {
    InputFileStream file(GetFilename(), std::ios::in | std::ios::binary);
    if (!file) {
      throw std::ios_base::failure("Failed to open file for reading");
    }
    StringType line;
    std::getline(file, line, '\n');
    return line;
  }

  void Append(const String& data) const {
    OutputFileStream file(GetFilename(),
                          std::ios::out | std::ios::app | std::ios::binary);
    if (!file) {
      throw std::ios_base::failure("Failed to open file for appending");
    }
    file << data;
  }

  void Clear() const {
    const OutputFileStream file(
        GetFilename(), std::ios::out | std::ios::trunc | std::ios::binary);
    if (!file) {
      throw std::ios_base::failure("Failed to open file for clearing");
    }
  }

private:
  [[nodiscard]] StringType GetFilename() const {
    return filename_.ToStdString();
  }

private:
  String filename_{};
};

using File = UnicodeFile<Char>;

}  // namespace unicore

#endif  // UNICORE_TYPES_UTF8_FILE_H_
