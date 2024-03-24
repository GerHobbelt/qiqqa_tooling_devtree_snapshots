#include <Eigen/Dense>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_arr_cwise_other_main
#endif

int main() {
  Eigen::ArrayXf a = Eigen::ArrayXf::Random(5);
  a *= 2;
  std::cout << "a =" << std::endl << a << std::endl;
  std::cout << "a.abs() =" << std::endl << a.abs() << std::endl;
  std::cout << "a.abs().sqrt() =" << std::endl << a.abs().sqrt() << std::endl;
  std::cout << "a.min(a.abs().sqrt()) =" << std::endl << a.min(a.abs().sqrt()) << std::endl;
  return 0;
}
