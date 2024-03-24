#include <Eigen/Dense>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_arr_mult_main
#endif

int main() {
  Eigen::ArrayXXf a(2, 2);
  Eigen::ArrayXXf b(2, 2);
  a << 1, 2, 3, 4;
  b << 5, 6, 7, 8;
  std::cout << "a * b = " << std::endl << a * b << std::endl;
  return 0;
}
