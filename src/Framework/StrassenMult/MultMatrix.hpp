#include <cmath>
#include "Matrix.hpp"
#include "../Framework.hpp"


class MultMatrix : private Matrix, public Problem {
private:
  Matrix right;

  int resizeInPow2(Matrix mat) {
    return pow(2, ceil(log2(mat.getM())));
  }
public:
  using Matrix::getM;
  using Matrix::getN;

  MultMatrix(Matrix mat, Matrix mat2):
    Matrix(mat), right(mat2)
  {
    int size = resizeInPow2(mat);
    resize(size, size);
    right.resize(size, size);
  }

  Matrix getLeftMat(void) {
    return (Matrix)*this;
  }

  Matrix getRightMat(void) {
    return right;
  }
};
