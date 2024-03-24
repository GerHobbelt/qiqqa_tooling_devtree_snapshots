#include <Eigen/Dense>
#include <iostream>

using namespace std;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_blk_print_main
#endif

int main() {
  Eigen::MatrixXf m(4, 4);
  m << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16;
  cout << "Block in the middle" << endl;
  cout << m.block<2, 2>(1, 1) << endl << endl;
  for (int i = 1; i <= 3; ++i) {
    cout << "Block of size " << i << "x" << i << endl;
    cout << m.block(0, 0, i, i) << endl << endl;
  }
  return 0;
}
