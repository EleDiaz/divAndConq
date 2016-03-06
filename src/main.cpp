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


int main(int argc, char *argv[]) {
#ifndef STATS
  vector<RandNum> vec {9,8,7,56,4,2,1,47};

  MSData data (&vec);
  MergeSort sorter;

  sorter.solve(data);

  for (int elem : *data.getVec()) {
    cout << elem <<  " ";
  }
  cout << endl;

  Matrix a = Matrix(4, 4, [] (int i, int j) { return RandNum();});
  a.output();
  Matrix b = Matrix(4, 4, [] (int i, int j) { return RandNum();});
  b.output();
  StrassenMult multiplier;

  multiplier.solve(MultMatrix(a, b)).output();
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

