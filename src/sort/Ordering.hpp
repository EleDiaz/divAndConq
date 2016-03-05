#pragma once
#include <string>
#include <iostream>
#include "../containers/Vector.hpp"

#ifdef DEBUG
     #define trace(msg) std::cout << msg;
#else
     #define trace(msg)
#endif // DEBUG

using namespace std;

template <class V>
class Ordering
{
protected:
  string name;
public:
  Ordering(string name): name(name) {}
  virtual void sort(Vector<V> & vec) = 0;
  virtual ~Ordering() {};
  const string getName() const {
    return name;
  }
  bool isSorted(Vector<V> & vec);
};

template <class V>
bool Ordering<V>::isSorted(Vector<V> & vec) {
  bool sorted = true;
  int i = 0;
  while (sorted && (i < vec.getSize()-1)) {
    sorted = vec[i] <= vec[i+1];
    if (!sorted)
      std::cout << "Aqui mal la "<< vec[i] << "  " << vec[i+1] << std::endl;
    i++;
  }
  return sorted;
}
