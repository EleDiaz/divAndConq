#pragma once
#include <iostream>
#include <tuple>
#include "../Framework.hpp"
#include "Matrix.hpp"
#include "MultMatrix.hpp"
#include "../../RandNum.hpp"

typedef RandNum VAL;

/*
Problem → (Matrix, Matrix), Solution → Matrix

isSimple :: (Matrix, Matrix) -> Bool
simplySolve :: (Matrix, Matrix) -> Matrix
combine :: (Matrix, Matrix) -> [] Matrix
decompose :: (Matrix, Matrix) -> [] (Matrix, Matrix)
*/

class StrassenMult : public DivAndConquer<MultMatrix, Matrix> {
private:
  Matrix combine(MultMatrix p, vector<Matrix> ss);

  bool isSimple(MultMatrix p);

  Matrix simplySolve(MultMatrix p);

  vector<MultMatrix *> decompose(MultMatrix p);

public:
  StrassenMult() {};
};


bool StrassenMult::isSimple(MultMatrix data) {
  return (data.getM() == 1 && data.getN() == 1);
}

Matrix StrassenMult::simplySolve(MultMatrix problem) {
  Matrix a = problem.getLeftMat();
  Matrix b = problem.getRightMat();
  return Matrix(1, 1, [=] (int,int) { return a.get(1, 1) * b.get(1, 1);});
}

Matrix StrassenMult::combine(MultMatrix p, vector<Matrix> ss) {
  Matrix c11 = ss[0].sum(ss[3]).subtract(ss[4]).sum(ss[6]);
  cout << "c11" << endl;
  c11.output();
  Matrix c12 = ss[2].sum(ss[4]);
  cout << "c12" << endl;
  c12.output();
  Matrix c21 = ss[1].sum(ss[3]);
  cout << "c21" << endl;
  c21.output();
  Matrix c22 = ss[0].subtract(ss[1]).sum(ss[2]).sum(ss[5]);
  cout << "c22" << endl;
  c22.output();
  return Matrix(p.getM(), p.getN(), c11, c12, c21, c22);
}

vector<MultMatrix *> StrassenMult::decompose(MultMatrix problem) {
  vector<MultMatrix *> result(7);

  Matrix a = problem.getLeftMat();
  Matrix b = problem.getRightMat();
  //cout << "Decompose" << endl;
  //a.output();
  //b.output();

  result[0] = new MultMatrix(a.getMatrixSquare(1, 1).sum(a.getMatrixSquare(2, 2)),
                             b.getMatrixSquare(1, 1).sum(b.getMatrixSquare(2, 2)));

  result[1] = new MultMatrix(a.getMatrixSquare(2, 1).sum(a.getMatrixSquare(2, 2)),
                             b.getMatrixSquare(1, 1));

  result[2] = new MultMatrix(a.getMatrixSquare(1, 1),
                             b.getMatrixSquare(1, 2).subtract(b.getMatrixSquare(2, 2)));

  result[3] = new MultMatrix(a.getMatrixSquare(2, 2),
                             b.getMatrixSquare(2, 1).subtract(b.getMatrixSquare(1, 1)));

  result[4] = new MultMatrix(a.getMatrixSquare(1, 1).sum(a.getMatrixSquare(1, 2)),
                             b.getMatrixSquare(2, 2));

  result[5] = new MultMatrix(a.getMatrixSquare(2, 1).subtract(a.getMatrixSquare(1, 1)),
                             b.getMatrixSquare(1, 1).sum(b.getMatrixSquare(1, 2)));

  result[6] = new MultMatrix(a.getMatrixSquare(1, 2).subtract(a.getMatrixSquare(2, 2)),
                             b.getMatrixSquare(2, 1).sum(b.getMatrixSquare(2, 2)));
  return result;
}
