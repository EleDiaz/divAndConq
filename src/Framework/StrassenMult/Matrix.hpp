#pragma once
#include <functional>
#include <vector>

using namespace std;

typedef int VAL;

class Matrix {
private:
  vector<VAL> rawData;
  int m; // columnas
  int n; // filas
public:

  Matrix(void): rawData() {
  }

  Matrix(int m, int n): rawData(m*n) {
  }

  Matrix(int m, int n, function<VAL (int i, int j)> fun): rawData(m*n) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        set(i, j, fun(i, j));
      }
    }
  }

  int getM() const {
    return m;
  }

  int getN() const {
    return n;
  }

  VAL get(int i, int j) const {
    return rawData[i+(j*m)];
  }

  void set(int i, int j, VAL elem) {
    rawData[i+(j*m)] = elem;
  }

  Matrix getMatrixSquare(int sectorI, int sectorJ) {
    return Matrix(m/2, n/2, [=] (int i, int j) {
        return get(i*sectorI, j*sectorJ);
      });
  }

  Matrix sum(Matrix mat) {
    return Matrix(m, n, [=] (int i, int j) {
        return get(i, j) + mat.get(i, j);
      });
  }

  Matrix subtract(Matrix mat) {
    return Matrix(m, n, [=] (int i, int j) {
        return get(i, j) - mat.get(i, j);
      });
  }

  // Matrix overSquare(int i, int j, Matrix...Ops...Matrix);
};
