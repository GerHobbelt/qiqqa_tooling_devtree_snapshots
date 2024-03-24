#include <Eigen/Dense>
#include <iostream>

using namespace std;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_blk_colrow_main
#endif

int main() {
  Eigen::MatrixXf m(3, 3);
  m << 1, 2, 3, 4, 5, 6, 7, 8, 9;
  cout << "Here is the matrix m:" << endl << m << endl;
  cout << "2nd Row: " << m.row(1) << endl;
  m.col(2) += 3 * m.col(0);
  cout << "After adding 3 times the first column into the third column, the matrix m is:\n";
  cout << m << endl;
  return 0;
}
