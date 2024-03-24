#if !defined(__U8_TO_STD_STRING_HELPER__)
#define      __U8_TO_STD_STRING_HELPER__
// #pragma once

#ifdef __cplusplus

#include <string>

// operator `""_ss` as per https://en.cppreference.com/w/cpp/language/user_literal
static constexpr inline std::string operator ""_ss(const char8_t* data, size_t len) {
	return std::string((const char *)data, len);
}

static constexpr inline std::string operator ""_ss(const char* str) {
	return std::string(str);
}

#define U8_SS(str)			std::string((const char *)(str))

#endif   // __cplusplus


#define U8_CC(str)			((const char *)(str))

#endif   // __U8_TO_STD_STRING_HELPER__
