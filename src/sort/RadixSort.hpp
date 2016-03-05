#pragma once
#include "../containers/List.hpp"
#include "../containers/Vector.hpp"
#include "Ordering.hpp"
#include <iostream>
template <class VAL>
class RadixSort : public Ordering<VAL>
{
private:
public:
  RadixSort(): Ordering<VAL>("RadixSort") {};
  void sort(Vector<VAL> & vec);
};

// TODO: incrementar el contador de las claves
template <class VAL>
void RadixSort<VAL>::sort(Vector<VAL> & vec) {

  Vector<List<VAL> > stacks(10);

  for (int i = 1; i < 9; i++) {
    trace("Radical " << i << endl)
    for (int j = 0; j < vec.getSize(); j++) {
      vec[j]>vec[j]; // TODO: esto
      stacks[(int(vec[j])%int(pow(10,i)))/int(pow(10,i-1))].snoc(vec[j]);
    }
    for (int z = 0; z < stacks.getSize(); z++) {
      trace("By number " << z << ": "<< stacks[z] << endl);
    }

    int ixV = 0;
    for (int t = 0; t < stacks.getSize(); t++) {
      while (!stacks[t].isEmpty()) {
        vec[ixV] = stacks[t].popFront();
        ixV++;
      }
    }
    trace("Vector: " << vec << endl);
  }
}
