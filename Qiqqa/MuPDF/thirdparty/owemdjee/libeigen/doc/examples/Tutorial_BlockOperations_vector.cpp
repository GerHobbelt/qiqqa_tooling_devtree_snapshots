#include <Eigen/Dense>
#include <iostream>

using namespace std;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_blk_vector_main
#endif

int main() {
  Eigen::ArrayXf v(6);
  v << 1, 2, 3, 4, 5, 6;
  cout << "v.head(3) =" << endl << v.head(3) << endl << endl;
  cout << "v.tail<3>() = " << endl << v.tail<3>() << endl << endl;
  v.segment(1, 4) *= 2;
  cout << "after 'v.segment(1,4) *= 2', v =" << endl << v << endl;
  return 0;
}
