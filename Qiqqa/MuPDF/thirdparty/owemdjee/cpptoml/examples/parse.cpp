#include "cpptoml.h"

#include <iostream>
#include <cassert>

#include "monolithic_examples.h"

#if defined(BUILD_MONOLITHIC)
#define main cpptoml_parse_example_main
#endif

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    try
    {
        std::shared_ptr<cpptoml::table> g = cpptoml::parse_file(argv[1]);
        std::cout << (*g) << std::endl;
    }
    catch (const cpptoml::parse_exception& e)
    {
        std::cerr << "Failed to parse " << argv[1] << ": " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
