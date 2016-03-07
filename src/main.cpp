#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>
#include <sstream>
#include <iomanip>
#include <functional>
#include <vector>
#include "Framework/Framework.hpp"
#include "Framework/MergeSort/MergeSort.hpp"
#include "Framework/StrassenMult/StrassenMult.hpp"

#include "sort/Insertion.hpp"

#include "Test.hpp"

using namespace std;

Counter RandNum::counter;


void testInsertion(int nPruebas, int step, int end) {
  for (int i = step; i < end; i+=step) {
    cout << i << " ";
    for (int j = 0; j < nPruebas; j++) {
      Vector<RandNum> data(i);
      RandNum::counter.start();
      Insertion<RandNum> insertion;
      insertion.sort(data);
      RandNum::counter.stop();
    }
    cout << RandNum::counter.getMin()
         << " " << RandNum::counter.getAccum()/nPruebas
         << " " << RandNum::counter.getMax() << endl;
    RandNum::counter.reset();
  }
}


void testMerge(int nPruebas, int step, int end) {
  for (int i = step; i < end; i+=step) {
    cout << i << " ";
    for (int j = 0; j < nPruebas; j++) {
      vector<RandNum> vec(i);
      MSData data(&vec);
      RandNum::counter.start();
      MergeSort sorter;
      sorter.solve(data);
      RandNum::counter.stop();
    }
    cout << RandNum::counter.getMin()
         << " " << RandNum::counter.getAccum()/nPruebas
         << " " << RandNum::counter.getMax() << endl;
    RandNum::counter.reset();
  }
}

void sortInN(void) {
  cout << "Tamaño: " << flush;
  int n;
  cin >> n;
  vector<RandNum> vec(n);
  MSData data (&vec);
  MergeSort sorter;
  sorter.solve(data);

  cout << *data.getVec() << endl;
}

void multRandNxM(void) {
  cout << "Tamaño n m: " << flush;
  int n, m;
  cin >> n;
  cin >> m;
  Matrix a = Matrix(n, m, [] (int i, int j) { return RandNum();});
  a.output();
  Matrix b = Matrix(n, m, [] (int i, int j) { return RandNum();});
  b.output();
  StrassenMult multiplier;
  multiplier.solve(MultMatrix(a, b)).output();
}

void multNxM(void) {
  cout << "Tamaño n m: " << flush;
  int n, m;
  cin >> n;
  cin >> m;
  Matrix a = Matrix(n, m, [] (int i, int j) { int a; cin >> a; return a;});
  a.output();
  Matrix b = Matrix(n, m, [] (int i, int j) { int a; cin >> a; return a;});
  b.output();
  StrassenMult multiplier;
  multiplier.solve(MultMatrix(a, b)).output();
}

int main(int argc, char *argv[]) {
#ifndef STATS
  // int n= 10;
  // Matrix a11(4,4, [&] (int, int j) {return j;});
  // a11.output();
  // n=20;
  // Matrix a12(4,4, [&] (int i, int) {return n++;});
  // n=30;
  // Matrix a21(4,4, [&] (int, int) {return n++;});
  // n=40;
  // Matrix a22(4,4, [&] (int, int) {return n++;});
  // Matrix full = Matrix(8, 8, a11, a12, a21, a22);
  // full.output();
  // full.getMatrixSquare(1, 1).output();
  // full.getMatrixSquare(1, 2).output();
  // full.getMatrixSquare(2, 1).output();
  // full.getMatrixSquare(2, 2).output();
  // int n;
  // Matrix a1(4,4, [&] (int, int ) {return n++;});
  // a1.output();
  // Matrix a2(4,4, [&] (int, int ) {return --n;});
  // a2.output();
  // a2.subtract(a1).output();

  int option;
  do {
    cout << "Menu:" << endl
         << "1 → Ordenar vector aleatorio de tamaño n" << endl
         << "2 → Multiplicar dos matriz aleatoria de tamaño n x m" << endl
         << "3 → Introducir matrices de n x m" << endl
         << "4 → Exit Door" << endl;
    cin >> option;

    switch (option) {
    case 1:
      sortInN();
      break;
    case 2:
      multRandNxM();
      break;
    case 3:
      multNxM();
      break;
    case 4:
      break;
    }
  } while (option!=4);

#else
  srand (time(NULL));

  cout << "Algoritmos de ordenacion usando 15 pruebas por tamanio" << endl;
  cout << "MergeSort" << endl;
  testMerge(10, 10, 300);
  cout << "Insertion" << endl;
  testInsertion(10, 10, 300);
#endif
  return 0;
}

