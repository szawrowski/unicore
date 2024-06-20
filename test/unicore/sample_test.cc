#include <fstream>

#include <gtest/gtest.h>

#include "unicore/unicore.h"

template <typename CharType>
static void PrintHexValue(CharType ch) {
  std::cout << std::hex << std::uppercase << std::setw(sizeof(CharType) * 2)
            << std::setfill('0');
  if (sizeof(CharType) == 2) {
    std::cout << reinterpret_cast<const uint16_t&>(ch);
  } else if (sizeof(CharType) == 4) {
    std::cout << reinterpret_cast<const uint32_t&>(ch);
  }
}

template <typename StringType>
static void PrintHex(StringType str) {
  for (auto ch : str) {
    PrintHexValue(ch);
    std::cout << ' ';
  }
  std::cout << std::endl;
}

void Func() {
  uni::String hello_world = "Hello, 世界! 😄";

  std::cout << "String: " << hello_world << " (char count: "
            << hello_world.CharCount() << ", " << "byte count: "
            << hello_world.ByteCount() << ')' << std::endl;

  std::cout << "UTF-16: ";
  PrintHex(hello_world.ToU16String());

  std::cout << "UTF-32: ";
  PrintHex(hello_world.ToU32String());

  std::cout << "Chars: ";
  for (const auto& c : hello_world) {
    std::cout << '\'' << c << "' ";
  }
  std::cout << std::endl;

  for (auto& c : hello_world) {
    if (c == "H") {
      c = "世";
    }
  }
  std::cout << "Modified chars: ";
  for (const auto& c : hello_world) {
    std::cout << '\'' << c << "' ";
  }
  std::cout << std::endl;

  const uni::Char emoji = "😄";

  std::cout << "Symbol: " << emoji << " (codepoint: " << std::hex
            << emoji.GetCodepoint() << std::dec << ')' << std::endl;

  const uni::String first_line = "First line 😄";
  const uni::String second_line = "Second line 😄";

  const auto file = uni::File{"file.txt"};
  file.Clear();
  file.WriteLine(first_line);
  file.Append(second_line);

  const auto input = file.Read();
  std::cout << input << std::endl;

  // ---------------------------------------------------------------------------

  uni::U16String str16 = u"Hello, 世界! 😄";
  std::cout << "Hex: ";
  PrintHex(str16.ToU16String());
  std::cout << "Converted from UTF-16 string: " << str16.ToStdString() << std::endl;

  // ---------------------------------------------------------------------------

  uni::U32String str32 = U"Hello, 世界! 😄";
  std::cout << "Hex: ";
  PrintHex(str32.ToU32String());
  std::cout << "Converted from UTF-32 string: " << str32.ToStdString()  << std::endl;

  std::cout << "Write char: " << uni::U32Char{U"😄"} << std::endl;
}

TEST(UnicoreTest, Sample) {
  Func();
  ASSERT_TRUE(true);
}
