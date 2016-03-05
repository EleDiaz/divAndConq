#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <functional>
#include <vector>
#include "Framework/Framework.hpp"
#include "Framework/MergeSort/MergeSort.hpp"


using namespace std;

int main(int argc, char *argv[])
{
  vector<int> vec {9,8,7,56,4,2,1,47};

  MSData data (&vec);
  MergeSort sorter;

  sorter.solve(data);

  for (int elem : *data.getVec()) {
    cout << elem <<  " ";
  }
  cout << endl;

// #ifdef DEBUG

//   if (argc == 2) {
//     Vector<DNI> vec(10);
//     cout << vec << endl;
//     sorters[stoi(argv[1])]->sort(vec);
//     cout << vec << endl;
//     cout << (sorters[0]->isSorted(vec)?
//              "Esta Ordenado" : "No Esta Ordenado") << endl;
//   }
//   else {
//     cout << "Format input is the following:\n"
//          << "\t ./program_name ord_choose\n\n"
//          << "\tord_choose : Int\n"
//          << "\tord_choose posibilities:\n"
//          << "\t\t\t0 -> Seletion, 1 -> Insertion, 2 -> QuickSort,\n"
//          << "\t\t\t3 -> MergeSort, 4 -> ShellSort, 5 -> RadixSort\n" << endl;
//   }

// #else

//   if (argc == 3) {
//     //testSet(stoi(argv[1]), stoi(argv[2]), sorters);
//   }
//   else {
//     cout << "Format input is the following:\n"
//          << "\t ./program_name number_test size_to_sort\n\n"
//          << "\tnumber_test, size_to_sort : Int\n" << endl;
//   }

// #endif
//   //sorters.map([](Ordering<DNI> * ord) { delete ord; return nullptr;});
//   return 0;
}

