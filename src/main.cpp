#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <functional>
#include "DNI.hpp"
#include "sort/Insertion.hpp"
#include "sort/Selection.hpp"
#include "sort/MergeSort.hpp"
#include "sort/QuickSort.hpp"
#include "sort/ShellSort.hpp"
#include "sort/RadixSort.hpp"
// #include "containers/List.hpp"

#include "Test.hpp"

Counter DNI::counter;

using namespace std;

int main(int argc, char *argv[])
{
  using namespace placeholders;

  // // Funcion de sedgewick para el shell sort
  // auto sedgewick = [] (int value) {
  //   static List<int> sedValues;
  //   if (!sedValues.isEmpty())
  //     return sedValues.pop();
  //   else {
  //     // TODO: me falta la otra formula e ir cambiando
  //     // 9*4^k - 9*2^k + 1
  //     int aux = pow(4,sedValues.length()+1)- 3 * pow(2,sedValues.length()+1)+1;
  //     while (aux <= value) {
  //       sedValues.cons(aux);
  //       aux = pow(4,sedValues.length()+1)- 3 * pow(2,sedValues.length()+1)+1;
  //     }
  //     cout << sedValues << endl;
  //     return sedValues.pop();
  //   }
  // };

  // // Funcion de hibbard para el shell sort
  // auto hibbard = [] (int value) {
  //   static List<int> hibbardValues;
  //   if (!hibbardValues.isEmpty())
  //     return hibbardValues.pop();
  //   else {
  //     int aux = (pow(3,hibbardValues.length()+1)-1) /2;
  //     while (aux <= value) {
  //       hibbardValues.cons(aux);
  //       aux = (pow(3,hibbardValues.length()+1)-1) /2;
  //     }
  //     cout << hibbardValues << endl;
  //     return hibbardValues.pop();
  //   }
  // };

  // Funcion alpha para el shellSort
  auto alphaF = [](float alpha, int value){
      return (alpha*value);
  };
  srand(time(0));
  Vector<Ordering<DNI> *> sorters =
    { new Selection<DNI>(),
      new Insertion<DNI>(),
      new QuickSort<DNI>(),
      new MergeSort<DNI>(),
      // new ShellSort<DNI>(sedgewick),
      // new ShellSort<DNI>(hibbard),
      new ShellSort<DNI>(bind(alphaF, 0.9, _1)),
      new RadixSort<DNI>()
    };

#ifdef DEBUG

  if (argc == 2) {
    Vector<DNI> vec(10);
    cout << vec << endl;
    sorters[stoi(argv[1])]->sort(vec);
    cout << vec << endl;
    cout << (sorters[0]->isSorted(vec)?
             "Esta Ordenado" : "No Esta Ordenado") << endl;
  }
  else {
    cout << "Format input is the following:\n"
         << "\t ./program_name ord_choose\n\n"
         << "\tord_choose : Int\n"
         << "\tord_choose posibilities:\n"
         << "\t\t\t0 -> Seletion, 1 -> Insertion, 2 -> QuickSort,\n"
         << "\t\t\t3 -> MergeSort, 4 -> ShellSort, 5 -> RadixSort\n" << endl;
  }

#else

  if (argc == 3) {
    testSet(stoi(argv[1]), stoi(argv[2]), sorters);
  }
  else {
    cout << "Format input is the following:\n"
         << "\t ./program_name number_test size_to_sort\n\n"
         << "\tnumber_test, size_to_sort : Int\n" << endl;
  }

#endif
  sorters.map([](Ordering<DNI> * ord) { delete ord; return nullptr;});
  return 0;
}

