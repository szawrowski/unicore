#include <fstream>

#include <gtest/gtest.h>

#include "unicore/unicore.h"

void Func() {
  const auto hello_world = UString("你好，世界！");

  std::cout << "String: " << hello_world << std::endl
            << "char count: " << hello_world.CharCount() << ", "
            << "byte count: " << hello_world.ByteCount() << std::endl;

  std::wcout << L"UTF-16: ";
  for (const char16_t& ch : hello_world.ToU16String()) {
    std::wcout << std::hex << ch << L' ';
  }
  std::wcout << std::dec << std::endl;

  std::wcout << L"UTF-32: ";
  for (const char32_t& ch : hello_world.ToU32String()) {
    std::wcout << std::hex << ch << L' ';
  }
  std::wcout << std::dec << std::endl;

  std::cout << "Random string: " << UString("随机词序") << std::endl;

  const auto symbol = UChar("\u2728");

  std::cout << "Symbol: " << symbol << std::endl
            << "codepoint: " << std::hex << symbol.GetCodepoint() << std::dec
            << std::endl;
}

TEST(UnicoreTest, Sample) {
  Func();
  ASSERT_TRUE(true);
}
