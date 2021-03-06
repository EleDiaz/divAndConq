#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include "../Framework.hpp"
#include "../../RandNum.hpp"

using namespace std;

typedef RandNum VAL;

class Matrix : public Solution {
private:
  vector<VAL> rawData;
  int m; // filas
  int n; // columnas
public:

  Matrix(void): rawData(), m(0), n(0) {
  }

  Matrix(int m, int n): rawData(m*n), m(m), n(n) {
  }

  Matrix(int m, int n, function<VAL (int i, int j)> fun): rawData(m*n), m(m), n(n) {
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        set(i, j, fun(i, j));
      }
    }
  }

  Matrix(int m, int n, Matrix a11, Matrix a12, Matrix a21, Matrix a22): rawData(m*n), m(m), n(n) {
    for (int i = 1; i <= m/2; i++) {
      for (int j = 1; j <= n/2; j++) {
        set(i, j, a11.get(i, j));
      }
    }

    for (int i = m/2+1; i <= m; i++) {
      for (int j = 1; j <= n/2; j++) {
        set(i, j, a21.get(i-(m/2), j));
      }
    }

    for (int i = 1; i <= m/2; i++) {
      for (int j = n/2+1; j <= n; j++) {
        set(i, j, a12.get(i, j-(n/2)));
      }
    }

    for (int i = m/2+1; i <= m; i++) {
      for (int j = n/2+1; j <= n; j++) {
        set(i, j, a22.get(i-(m/2), j-(n/2)));
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
    return rawData[(i-1)+((j-1)*n)];
  }

  void set(int i, int j, VAL elem) {
    rawData[(i-1)+((j-1)*n)] = elem;
  }

  Matrix getMatrixSquare(int sectorI, int sectorJ) {
    return Matrix(m/2, n/2, [=] (int i, int j) {
        return get(i+(sectorI-1)*n/2, j+(sectorJ-1)*m/2);
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

  void output(void) {
    cout << "Matrix" << endl;
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        cout << get(i, j) << " ";
      }
      cout << endl;
    }
  }

  void resize(int m, int n) {
    if (m == getM() && n == getN()) {
      return;
    }
    else {
      Matrix aux = Matrix(m, n, [=] (int i, int j) {
          if (getM()>=i && getN()>=j)
            return get(i,j);
          else
            return VAL(0);
        });
      this->rawData = aux.rawData;
      this->m       = aux.m;
      this->n       = aux.n;
    }
  }

  // Matrix overSquare(int i, int j, Matrix...Ops...Matrix);
};
