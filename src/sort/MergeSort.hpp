#pragma once
#include <tuple>
#include "Ordering.hpp"

typedef pair<int, int> TuplaXY;

template <class VAL>
class MergeSort : public Ordering<VAL>
{
private:
  TuplaXY unionVec(TuplaXY xs, TuplaXY ys, Vector<VAL> & vec);
  int min(int a, int b) { return (a>b)?b:a; }
public:
  MergeSort(): Ordering<VAL>("MergeSort") {};
  void sort(Vector<VAL> & vec);
};


template <class VAL>
TuplaXY MergeSort<VAL>::unionVec(TuplaXY xs,
                                 TuplaXY ys,
                                 Vector<VAL> & vec) {
    int i = xs.first;
    int j = ys.first;
    Vector<int> vecAux;
    vecAux.resize(ys.second-xs.first+1);
    for (int k = 0; k<vecAux.getSize(); k++) {
      trace("Valores: [" << i << ":" << j << "]" << endl;)
        if (i > xs.second) {
          trace("j++ "<<j+1<<endl);
            vecAux[k] = vec[j];
            j++;
        }
        else if (j > ys.second) {
          trace("i++ "<< i+1<< endl);
            vecAux[k] = vec[i];
            i++;
        }
        else if (vec[i] < vec[j]) {
          trace("i++ "<< i+1<<endl);
            vecAux[k] = vec[i];
            i++;
        }
        else {
          trace("j++ " << j+1 << endl);
            vecAux[k] = vec[j];
            j++;
        }
      trace("VecAux: " << vecAux << endl);
    }
    trace("sub-Vector [ ");
    for (int i=0; i<vecAux.getSize();i++) {
        vec[xs.first+i]=vecAux[i];
        trace(vecAux[i] << " ");
    }
    trace("]" << endl);
    return pair<int, int> {xs.first,ys.second};
}

template <class VAL>
void MergeSort<VAL>::sort(Vector<VAL> & vec) {
  for (int i = 1; i < vec.getSize(); i*=2) {
    trace(i << ": " << endl);
    for (int j = 0; j < vec.getSize(); j+=2*i) {
      int split = (j + j+2*i) / 2;
      int resto = (j + j+2*i) % 2;
      trace(setw(10) << "[" << j << ":" << min((j+2*i)-1,vec.getSize()-1) << "]  ");
      unionVec(pair<int,int> { j, resto == 0 ? split-1 : split},
               pair<int,int> { resto == 0 ?
                   split
                   :
                   min(split+1, vec.getSize()-1), min((j+2*i)-1,vec.getSize()-1) },
               vec);
    }
  }
}



