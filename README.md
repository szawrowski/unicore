# Unicore

### About
This toolkit ensures proper handling of UTF-8 strings.
The **string** class functions as a wrapper around a vector of
Unicode code points, with each code point occupying 4 bytes.
While this storage method may not be the most space-efficient,
particularly when compactness is important,
it allows for accurate handling of multi-byte characters.
The library provides support for individual characters, strings,
and file streams, and its usage is largely consistent with standard methods.

### Usage
```c++
#include <unicore/unicore.h>

int main() {
  const auto str = "Hello, 世界!"_str;
  const auto emoji = "🙂"_char;
  std::cout << str << ' ' << emoji << std::endl;
  return 0;
}
```

### Output
```
Hello, 世界! 🙂
```
