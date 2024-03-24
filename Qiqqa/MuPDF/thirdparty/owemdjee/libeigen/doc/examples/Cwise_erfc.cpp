#include <Eigen/Core>
#include <unsupported/Eigen/SpecialFunctions>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_cwise_erfc_main
#endif

int main() {
  Eigen::Array4d v(-0.5, 2, 0, -7);
  std::cout << v.erfc() << std::endl;
  return 0;
}
