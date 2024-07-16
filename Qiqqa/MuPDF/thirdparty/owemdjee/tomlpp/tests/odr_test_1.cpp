#define TOML_UNDEF_MACROS 0
#include "../toml.hpp"

TOML_DISABLE_WARNINGS;


#if defined(BUILD_MONOLITHIC)
#define main      toml_odr_test_1_main
#endif

int main()
{
	return 0;
}
