#pragma once
#include "Ordering.hpp"


template <class VAL>
class Selection : public Ordering<VAL>
{
public:
  Selection(): Ordering<VAL>("Selection") {};
  void sort(Vector<VAL> & vec);
};

template <class VAL>
void Selection<VAL>::sort(Vector<VAL> & vec) {
  auto minNoSorted = [&vec] (int start) {
    int min = start;
    for (int i = start; i < vec.getSize(); i++)
      min = vec[min]>vec[i]? i : min;
    return min;
  };

  for (int i = 0; i < vec.getSize(); i++) {
    int min = minNoSorted(i);
    trace("min: " << min << "-> " << vec[min] << endl);
    vec.swap(i, min);
    trace(i << ": " << vec << endl);
  }
}
