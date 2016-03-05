#include <iostream>
#include "Counter.hpp"
#include "sort/Ordering.hpp"
#include "DNI.hpp"
#include "containers/Vector.hpp"

using namespace std;

void testSort(Ordering<DNI> * ord, int n) {
  Vector<DNI> vec(n);
  DNI::counter.start();
  ord->sort(vec);
  if (!ord->isSorted(vec)) {
    cout << "Mi**da Ups" << endl;
    cout << vec << endl;
  }
  DNI::counter.stop();
}

void testSet(int nPruebas, int sizeVec, Vector<Ordering<DNI> *> & vord) {

  cout << setw(30) << "Numero de comparaciones: "<< endl;
  cout << setw(25) << "Minimo" << setw(10) << "Medio" << setw(10) << "Maximo" << endl;
  vord.map([nPruebas, sizeVec](Ordering<DNI> * ord) {
      cout << setw(15) << ord->getName() << flush;
      for (int i = 0; i < nPruebas; i++) {
        testSort(ord, sizeVec);
      }
      cout << setw(10) << DNI::counter.getMin()
           << setw(10) << DNI::counter.getAccum()/nPruebas
           << setw(10) << DNI::counter.getMax() << endl;
      DNI::counter.reset();
      return ord;
    });
}
