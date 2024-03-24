#include <Eigen/Core>
#include <iostream>

// define function to be applied coefficient-wise
double ramp(double x) {
  if (x > 0)
    return x;
  else
    return 0;
}


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_class_cwise_ptrfun_main
#endif

int main() {
  Eigen::Matrix4d m1 = Eigen::Matrix4d::Random();
  std::cout << m1 << std::endl << "becomes: " << std::endl << m1.unaryExpr([](double x) { return ramp(x); }) << std::endl;
  return 0;
}
