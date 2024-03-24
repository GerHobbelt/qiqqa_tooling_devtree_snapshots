#include <iostream>
#include <Eigen/Dense>

using namespace std;


#if defined(BUILD_MONOLITHIC)
#define main eigen_doc_tutorial_redux_basic_main
#endif

int main() {
  Eigen::Matrix2d mat;
  mat << 1, 2, 3, 4;
  cout << "Here is mat.sum():       " << mat.sum() << endl;
  cout << "Here is mat.prod():      " << mat.prod() << endl;
  cout << "Here is mat.mean():      " << mat.mean() << endl;
  cout << "Here is mat.minCoeff():  " << mat.minCoeff() << endl;
  cout << "Here is mat.maxCoeff():  " << mat.maxCoeff() << endl;
  cout << "Here is mat.trace():     " << mat.trace() << endl;
  return 0;
}
