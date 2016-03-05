#include <functional>
#include "Ordering.hpp"

template <class VAL>
class ShellSort : public Ordering<VAL>
{
private:
  void deltaSort(int d, Vector<VAL> & vec);
  function<int (int)> deltaF;
public:
  ShellSort(function<int (int)> func): Ordering<VAL>("ShellSort"), deltaF(func){};
  void sort(Vector<VAL> & vec);
};

template <class VAL>
void ShellSort<VAL>::deltaSort(int d, Vector<VAL> & vec) {
  for (int i = d; i < vec.getSize(); i++) {
    VAL x = vec[i];
    int j = i;
    while ((j >= d) && (x < vec[j-d])) {
      trace(setw(10) << "j: " << j << " d: "<< d << endl)
      vec[j] = vec[j-d];
      j = j - d;
    };
    vec[j] = x;
    trace(setw(10) << " vec: " << vec << endl);
  };
};

template <class VAL>
void ShellSort<VAL>::sort(Vector<VAL> & vec) {
  int del = vec.getSize();
  while (del > 1) {
    del = deltaF(del);
    trace("Delta: " << del << endl);
    deltaSort(del,vec);
  };
}
