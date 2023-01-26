#ifndef REPLXX_UTIL_HXX_INCLUDED
#define REPLXX_UTIL_HXX_INCLUDED 1

#include "replxx.hxx"

namespace replxx {

namespace color {
static int unsigned const RGB666 = 16u;
static int unsigned const GRAYSCALE = 232u;
static int unsigned const BOLD = 1u << 17u;
static int unsigned const UNDERLINE = 1u << 18u;
static int unsigned const BACKGROUND_COLOR_SET = 1u << 19u;
}

inline bool is_control_code(char32_t testChar) {
	return (testChar < ' ') ||											// C0 controls
				 (testChar >= 0x7F && testChar <= 0x9F);	// DEL and C1 controls
}

inline char32_t control_to_human( char32_t key ) {
	return ( key < 27 ? ( key + 0x40 ) : ( key + 0x18 ) );
}

int virtual_render(char32_t const* display_, int size_, int& x_, int& y_, int screenColumns_, int promptLen_, char32_t* rendered_ = nullptr, int* renderedSize_ = nullptr);
char const* ansi_color(Replxx::Color color_);

std::string now_ms_str( void );

int mk_wcwidth(char32_t ucs);

}

#endif
