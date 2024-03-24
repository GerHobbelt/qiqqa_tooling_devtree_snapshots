#include <Eigen/Core>
#include <iostream>

template <typename Derived>
Eigen::Reshaped<Derived, 4, 2> reshape_helper(Eigen::MatrixBase<Derived>& m) {
  return Eigen::Reshaped<Derived, 4, 2>(m.derived());
}


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_class_fixed_reshaped_main
#endif

int main() {
  Eigen::MatrixXd m(2, 4);
  m << 1, 2, 3, 4, 5, 6, 7, 8;
  Eigen::MatrixXd n = reshape_helper(m);
  std::cout << "matrix m is:" << std::endl << m << std::endl;
  std::cout << "matrix n is:" << std::endl << n << std::endl;
  return 0;
}
