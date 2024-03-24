#include <Eigen/Core>
#include <iostream>

using Eigen::Matrix4d;

// define a custom template binary functor
template <typename Scalar>
struct MakeComplexOp {
  typedef std::complex<Scalar> result_type;
  result_type operator()(const Scalar& a, const Scalar& b) const { return result_type(a, b); }
};


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_example_class_cwise_binary_op_main
#endif

int main() {
  Matrix4d m1 = Matrix4d::Random(), m2 = Matrix4d::Random();
  std::cout << m1.binaryExpr(m2, MakeComplexOp<double>()) << std::endl;
  return 0;
}
