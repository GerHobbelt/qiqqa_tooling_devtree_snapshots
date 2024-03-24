#include <Eigen/Core>
#include <iostream>
#include <random>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_rand_cpp_main
#endif

int main() {
  std::default_random_engine generator;
  std::poisson_distribution<int> distribution(4.1);
  auto poisson = [&]() { return distribution(generator); };

  Eigen::RowVectorXi v = Eigen::RowVectorXi::NullaryExpr(10, poisson);
  std::cout << v << "\n";
  return 0;
}
