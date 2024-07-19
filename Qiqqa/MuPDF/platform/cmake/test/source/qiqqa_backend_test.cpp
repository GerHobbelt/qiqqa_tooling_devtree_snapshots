#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "qiqqa_backend" ? 0 : 1;
}
