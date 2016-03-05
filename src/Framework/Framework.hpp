#pragma once
#include <vector>
#include <type_traits>
#include "Solution.hpp"
#include "Problem.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>

template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec)
{
  os<<"{ ";
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
  os<<"}";
  return os;
}

using namespace std;

template<typename Pro, typename Sol>
using IsSubtypesProblemAndSolution = typename std::enable_if<std::is_base_of<Solution, Sol>::value && std::is_base_of<Problem, Pro>::value>::type;

template<class Sol, class Pro, class Enable = void>
class DivAndConquer {}; // primary template


template <class Sol, class Pro>
class DivAndConquer<Pro, Sol, IsSubtypesProblemAndSolution<Pro, Sol>> {
 public:
  DivAndConquer() {};

  Sol solve(Pro p) {
    vector<Pro *> pp;
    if (isSimple(p)) {
      cout << "Is Simple" << endl;
      return simplySolve(p);
    }
    else  {
      pp = decompose(p);
    }
    vector<Sol> ss; // (pp.size()); // = vector<Sol>(pp.size());
    for (unsigned i = 0; i < pp.size(); i++) {
      ss.push_back(solve(*pp[i]));
      delete pp[i];
    }
    return combine(p, ss);
  }

 protected:
  virtual bool isSimple(Pro p) = 0;

  virtual Sol simplySolve(Pro p) = 0;

  virtual vector<Pro *> decompose(Pro p) = 0;

  virtual Sol combine(Pro p, vector<Sol> ss) = 0;
};


// 1 2 4 4 5   3 5 5 6

// cojo y comparo 1 con el segundo


// if (vec i > vec j)
//   j quito vec j
//   else
//     ()
