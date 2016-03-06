#include <vector>
#include <iostream>
#include "Counter.hpp"
#include "RandNum.hpp"
#include "Framework/MergeSort/MergeSort.hpp"

using namespace std;

void testSort(MergeSort * sorter, int n) {
  vector<RandNum> vec(n);
  RandNum::counter.start();
  MSData data(&vec);
  sorter->solve(data);
  // if (!ord->isSorted(vec)) {
  //   cout << "Mi**da Ups" << endl;
  //   cout << vec << endl;
  // }
  RandNum::counter.stop();
}

void testSet(int nPruebas, int sizeVec, MergeSort * sorter) {

  //cout << "Numero de comparaciones: "<< endl;
  //cout << "Minimo"  << "Medio" << "Maximo" << endl;
  for (int i = 0; i < nPruebas; i++) {
    testSort(sorter, sizeVec);
  }
  cout << RandNum::counter.getMin()
       << " " << RandNum::counter.getAccum()/nPruebas
       << " " << RandNum::counter.getMax() << endl;
  RandNum::counter.reset();
}
