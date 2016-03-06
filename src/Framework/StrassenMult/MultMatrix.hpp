#include "Matrix.hpp"
#include "../Framework.hpp"


class MultMatrix : private Matrix, public Problem {
private:
  Matrix right;
public:
  using Matrix::getM;
  using Matrix::getN;

  MultMatrix(Matrix mat, Matrix mat2): Matrix(mat), right(mat2) {}

  Matrix getLeftMat(void) {
    return (Matrix)*this;
  }

  Matrix getRightMat(void) {
    return right;
  }
  // Se trata de una mult debes guardar las dos matrices para calcular si
  // es el caso mínimo
};
