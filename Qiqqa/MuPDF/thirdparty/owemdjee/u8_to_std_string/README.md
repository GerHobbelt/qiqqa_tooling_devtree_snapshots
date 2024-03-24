# C++ u8_to_std_string (`u8` and `char8_t` based string to `std::string`)  

C++ inlines to convert between `u8` (`char8_t[]`) string constants and `char`-based `std::string` types to shut up C++17 ➜ C++20 transitioning codebases & compilers.


## Usage

Simply `#include` the provided header file and use the `u8_ss` operator or `U8_SS(<string value>)` macro, e.g.

```
std::string s1 = u8_ss"börkbörkbörk Ärgh!";
std::string s2 = U8_SS("börkbörkbörk Bär!");

const char *s3 = U8_CC("börkbörkbörk Çlùnck!");

const char8_t *s4 = u8"börkbörkbörk ökidöki!";
// ^^^^^ no need for our special sauce here as there's no `char`-based type involved!
```

instead of this (which will produce compile-time errors in C++20 mode):

```
std::string s1 = u8"börkbörkbörk Ärgh!";
std::string s2 = u8"börkbörkbörk Bär!";

const char *s3 = u8"börkbörkbörk Çlùnck!";

const char8_t *s4 = u8"börkbörkbörk ökidöki!";      // no special sauce reqd.
```



