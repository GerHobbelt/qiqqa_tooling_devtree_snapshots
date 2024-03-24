#include <Eigen/Dense>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_arr_access_main
#endif

int main() {
  Eigen::ArrayXXf m(2, 2);

  // assign some values coefficient by coefficient
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = m(0, 1) + m(1, 0);

  // print values to standard output
  std::cout << m << std::endl << std::endl;

  // using the comma-initializer is also allowed
  m << 1.0, 2.0, 3.0, 4.0;

  // print values to standard output
  std::cout << m << std::endl;
  return 0;
}
