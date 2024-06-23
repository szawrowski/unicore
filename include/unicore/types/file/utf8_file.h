// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef UNICORE_TYPES_UTF8_FILE_H_
#define UNICORE_TYPES_UTF8_FILE_H_

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <utility>

#include "unicore/operators/string_stream_operator.h"
#include "unicore/types/file/unicode_file.h"
#include "unicore/types/string/utf8_string.h"

namespace uni {

template <>
class unicode_file<char_t> {
public:
  using char_type = char_t;
  using basic_char_type = char_type::char_type;
  using basic_string_type = std::basic_string<basic_char_type>;
  using file_stream_type = std::basic_fstream<basic_char_type>;
  using string_type = string;

  unicode_file() = default;

  explicit unicode_file(const string_type& filename)
      : filename_(filename.to_std_string()) {
    open();
  }

  unicode_file(const unicode_file& other) : filename_(other.filename_) {
    open();
  }

  unicode_file(unicode_file&& other) noexcept
      : filename_(std::move(other.filename_)), file_(std::move(other.file_)) {}

  ~unicode_file() { close(); }

  unicode_file& operator=(const unicode_file& other) {
    if (this != &other) {
      close();
      filename_ = other.filename_;
      open();
    }
    return *this;
  }

  unicode_file& operator=(unicode_file&& other) noexcept {
    if (this != &other) {
      close();
      filename_ = std::move(other.filename_);
      file_ = std::move(other.file_);
    }
    return *this;
  }

  void set_filename(const string_type& filename) {
    close();
    filename_ = filename.to_std_string();
    open();
  }

  [[nodiscard]] bool exists() const {
    return std::filesystem::exists(filename_);
  }

  [[nodiscard]] std::uintmax_t get_size() const {
    return std::filesystem::file_size(filename_);
  }

  void copy_to(const string_type& dest) const {
    std::filesystem::copy(filename_, dest.to_std_string(),
                          std::filesystem::copy_options::overwrite_existing);
  }

  void move_to(const string_type& dest) {
    std::filesystem::rename(filename_, dest.to_std_string());
    filename_ = dest.to_std_string();
    open();
  }

  void write(const string_type& data) {
    if (!file_.is_open() || !file_.good()) {
      open(std::ios::out | std::ios::binary);
    }
    file_.seekp(0, std::ios::beg);
    file_.write(data.to_std_string().c_str(),
                static_cast<std::streamsize>(data.size()));
    file_.flush();
  }

  void write_line(const string_type& data) {
    if (!file_.is_open() || !file_.good()) {
      open(std::ios::out | std::ios::app | std::ios::binary);
    }
    file_.seekp(0, std::ios::end);
    file_.write(data.to_std_string().c_str(),
                static_cast<std::streamsize>(data.size()));
    file_.put('\n');
    file_.flush();
  }

  [[nodiscard]] string_type read() {
    if (!file_.is_open() || !file_.good()) {
      open(std::ios::in | std::ios::binary);
    }
    file_.seekg(0, std::ios::beg);
    std::basic_ostringstream<basic_char_type> oss;
    oss << file_.rdbuf();
    return oss.str();
  }

  [[nodiscard]] string_type read_line() {
    if (!file_.is_open() || !file_.good()) {
      open(std::ios::in | std::ios::binary);
    }
    basic_string_type line;
    std::getline(file_, line);
    return line;
  }

  void append(const string_type& data) {
    if (!file_.is_open() || !file_.good()) {
      open(std::ios::out | std::ios::app | std::ios::binary);
    }
    file_.seekp(0, std::ios::end);
    file_.write(data.to_std_string().c_str(),
                static_cast<std::streamsize>(data.size()));
    file_.flush();
  }

  void clear() {
    if (file_.is_open()) {
      file_.close();
    }
    std::ofstream clear_file(
        filename_, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!clear_file) {
      throw std::ios_base::failure{"Failed to open file for clearing"};
    }
    clear_file.close();
    open();
  }

  void set_position(const std::streampos pos) {
    if (!file_.is_open()) {
      throw std::ios_base::failure{"File not open"};
    }
    file_.seekg(pos);
  }

  void reset_position() {
    if (!file_.is_open()) {
      throw std::ios_base::failure{"File not open"};
    }
    file_.seekg(0, std::ios::beg);
  }

private:
  void open(std::ios::openmode mode = std::ios::in | std::ios::out |
                                      std::ios::binary) {
    close();
    file_.open(filename_, mode);
    if (!file_) {
      throw std::ios_base::failure{"Failed to open file"};
    }
  }

  void close() {
    if (file_.is_open()) {
      file_.close();
    }
  }

  basic_string_type filename_;
  mutable file_stream_type file_;
};

}  // namespace uni

#endif  // UNICORE_TYPES_UTF8_FILE_H_
