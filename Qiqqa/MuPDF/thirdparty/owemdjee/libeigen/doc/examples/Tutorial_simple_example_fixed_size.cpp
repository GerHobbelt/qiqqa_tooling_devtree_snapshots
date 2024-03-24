#include <Eigen/Core>
#include <iostream>


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_fixed_size_main
#endif

int main() {
  Eigen::Matrix3f m3;
  m3 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
  Eigen::Matrix4f m4 = Eigen::Matrix4f::Identity();
  Eigen::Vector4i v4(1, 2, 3, 4);

  std::cout << "m3\n" << m3 << "\nm4:\n" << m4 << "\nv4:\n" << v4 << std::endl;
  return 0;
}
