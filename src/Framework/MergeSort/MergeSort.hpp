#pragma once
#include <iostream>
#include <tuple>
#include "../Framework.hpp"
#include "../../RandNum.hpp"

typedef pair<int, int> TuplaXY;

typedef RandNum VAL;

class MSData : public Problem, public Solution {
private:
  TuplaXY xs;
  vector<VAL> * vec;
public:
  vector<VAL>* getVec() {
    //cout << "getVec" << endl;
    return vec;
  }


  const TuplaXY getXs() const {
    return xs;
  }

  void setXs(const TuplaXY xs) {
    this->xs = xs;
  }

  MSData(const MSData & data):
    xs(data.xs), vec(data.vec)
  {}

  MSData(vector<VAL> * vec):
    xs(pair<int, int>{0, vec->size()-1}),
    vec(vec)
  {}

  MSData(TuplaXY xs, vector<VAL> * vec):
    xs(xs), vec(vec)
  {}

  MSData operator=(const MSData & data) {
    return data;
  }

};


class MergeSort : public DivAndConquer<MSData, MSData> {
private:
  MSData combine(MSData p, vector<MSData> ss);

  bool isSimple(MSData p);

  MSData simplySolve(MSData p);

  vector<MSData *> decompose(MSData p);

  int min(int a, int b) { return (a>b)?b:a; }
public:
  MergeSort() {};
  void sort(vector<VAL> & vec);
};

bool MergeSort::isSimple(MSData data) {
  return (data.getXs().second - data.getXs().first) <= 2;
}

MSData MergeSort::simplySolve(MSData data) {

  if (data.getVec()->at(data.getXs().first)
      >
      data.getVec()->at(data.getXs().second)) {

    VAL aux = data.getVec()->at(data.getXs().first);
    data.getVec()->at(data.getXs().first) = data.getVec()->at(data.getXs().second);
    data.getVec()->at(data.getXs().second) = aux;
  }
  return data;
}

MSData MergeSort::combine(MSData p, vector<MSData> ss) {
  if (ss.size() != 2) {
    throw "Todo falla";
  };
  vector<VAL>& vec = *p.getVec();
  TuplaXY xs = ss.at(0).getXs();
  TuplaXY ys = ss.at(1).getXs();
  int i = xs.first;
  int j = ys.first;
  vector<int> vecAux;
  vecAux.resize(ys.second-xs.first+1);
  for (unsigned k = 0; k<vecAux.size(); k++) {
    if (i > xs.second) {
      vecAux[k] = vec[j];
      j++;
    }
    else if (j > ys.second) {
      vecAux[k] = vec[i];
      i++;
    }
    else if (vec[i] < vec[j]) {
      vecAux[k] = vec[i];
      i++;
    }
    else {
      vecAux[k] = vec[j];
      j++;
    }
  }
  for (unsigned i=0; i<vecAux.size();i++) {
    vec[xs.first+i]=vecAux[i];
  }
  //cout << "join  " << vec << endl;
  return MSData(pair<int, int> {xs.first,ys.second}, &vec);
}

vector<MSData *> MergeSort::decompose(MSData data) {
  //cout << "decompose  " << *data.getVec() << endl;
  int middle = data.getXs().first + (data.getXs().second - data.getXs().first) / 2;
  //cout << "en " << data.getXs().first << " y " << middle << endl;
  //cout << "en " << middle+1 << " y " << data.getXs().second << endl;
  vector<MSData *> result(2);
  result[0] = new MSData(pair<int, int> {data.getXs().first, middle}, data.getVec());
  result[1] = new MSData(pair<int, int> {middle+1, data.getXs().second}, data.getVec());
  return result;
}
