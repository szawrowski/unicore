#include <iostream>
#include <gtest/gtest.h>
#include "unicore/unicore.h"

void func() {
  auto str = "Hello, 世界! 😄"_str;

  std::cout << "string: " << str << " (char count: " << str.char_count() << ", "
            << "byte count: " << str.byte_count() << ')' << std::endl;

  std::cout << "Chars: ";
  for (const auto& c : str) {
    std::cout << '\'' << c << "' ";
  }
  std::cout << std::endl;

  for (auto& c : str) {
    if (c == "H") {
      c = "世";
    }
  }
  std::cout << "Modified chars: ";
  for (const auto& c : str) {
    std::cout << '\'' << c << "' ";
  }
  std::cout << std::endl;

  // Symbol --------------------------------------------------------------------

  const auto emoji = "😄"_char;

  std::cout << "Symbol: " << emoji << " (codepoint: " << std::hex
            << emoji.get_codepoint() << std::dec << ')' << std::endl;

  // File ----------------------------------------------------------------------

  const auto first_line = "First line"_str;
  const auto second_line = "Second line"_str;

  auto file = uni::file{"example.txt"};
  file.clear();
  file.write_line(first_line);
  file.write_line(second_line);
  file.reset_position();

  auto line = file.read_line();
  std::cout << "First line: " << line << std::endl;
  line = file.read_line();
  std::cout << "Second line: " << line << std::endl;

  file.reset_position();
  const auto all = file.read();
  std::cout << "All content: '" << all << '\'' << std::endl;
}

TEST(UnicoreTest, Sample) {
  func();
  ASSERT_TRUE(true);
}
