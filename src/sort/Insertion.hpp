#pragma once
#include "Ordering.hpp"

template <class VAL>
class Insertion : public Ordering<VAL>
{
public:
  Insertion(): Ordering<VAL>("Insertion") {};
  void sort(Vector<VAL> & vec);
};

template <class VAL>
void Insertion<VAL>::sort(Vector<VAL> & vec) {
  for (int i = 1; i < vec.getSize(); i++) {
    int j = i;
    while (j > 0 && (vec[j] < vec[j-1])) {
      VAL aux = vec[j];
      vec[j] = vec[j-1];
      vec[j-1] = aux;
      j--;
    }
    trace(i << ": " << vec << endl);
  }
}

