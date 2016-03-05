#pragma once
#include <tuple>
#include "../Framework.hpp"

typedef pair<int, int> TuplaXY;

typedef int VAL;

class MSData : public Problem, public Solution {
private:
  TuplaXY xs;
  vector<VAL> & vec;
public:
  vector<VAL>& getVec() {
    return vec;
  }

  void setVec(const vector<VAL>& vec) {
    this->vec = vec;
  }

  const TuplaXY getXs() const {
    return xs;
  }

  void setXs(const TuplaXY xs) {
    this->xs = xs;
  }

  MSData(TuplaXY xs, vector<VAL> & vec):
    xs(xs), vec(vec)
  {}
};


class MergeSort : public DivAndConquer {
private:
  Solution combine(Problem p, vector<Solution> ss);

  bool isSimple(Problem p);

  Solution simplySolve(Problem p);

  vector<Problem> decompose(Problem p);

  int min(int a, int b) { return (a>b)?b:a; }
public:
  MergeSort() {};
  void sort(vector<VAL> & vec);
};

bool MergeSort::isSimple(Problem p) {
  MSData * data = static_cast<MSData *>(&p);
  return data->getVec().size() <= 2;
}

Solution MergeSort::simplySolve(Problem p) {
  MSData * data = static_cast<MSData *>(&p);
  if (data->getVec().at(data->getXs().first)
      >
      data->getVec().at(data->getXs().second)) {

    VAL aux = data->getVec().at(data->getXs().first);
    data->getVec().at(data->getXs().first) = data->getVec().at(data->getXs().second);
    data->getVec().at(data->getXs().second) = aux;
  }
  return (Solution)*data;
}

Solution MergeSort::combine(Problem p, vector<Solution> ss) {
  if (ss.size() != 2) {
    throw "Todo falla";
  };
  vector<VAL> vec = ((MSData *)&p)->getVec();
  TuplaXY xs = ((MSData *)&ss.at(0))->getXs();
  TuplaXY ys = ((MSData *)&ss.at(1))->getXs();
  int i = xs.first;
  int j = ys.first;
  vector<int> vecAux;
  vecAux.resize(ys.second-xs.first+1);
  for (unsigned k = 0; k<vecAux.size(); k++) {
    // trace("Valores: [" << i << ":" << j << "]" << endl;)
    if (i > xs.second) {
      // trace("j++ "<<j+1<<endl);
      vecAux[k] = vec[j];
      j++;
    }
    else if (j > ys.second) {
      // trace("i++ "<< i+1<< endl);
      vecAux[k] = vec[i];
      i++;
    }
    else if (vec[i] < vec[j]) {
      // trace("i++ "<< i+1<<endl);
      vecAux[k] = vec[i];
      i++;
    }
    else {
      // trace("j++ " << j+1 << endl);
      vecAux[k] = vec[j];
      j++;
    }
    // trace("VecAux: " << vecAux << endl);
  }
  // trace("sub-Vector [ ");
  for (unsigned i=0; i<vecAux.size();i++) {
    vec[xs.first+i]=vecAux[i];
    // trace(vecAux[i] << " ");
  }
  // trace("]" << endl);
  return (Solution)MSData(pair<int, int> {xs.first,ys.second}, vec);
}

vector<Problem> MergeSort::decompose(Problem p) {
  MSData * data = static_cast<MSData *>(&p);
  vector<Problem> result(2);
  int middle = data->getXs().first + (data->getXs().second - data->getXs().first) / 2;
  result[0] = (Problem)MSData(pair<int, int> {data->getXs().first, middle}, data->getVec());
  result[1] = (Problem)MSData(pair<int, int> {middle+1, data->getXs().second}, data->getVec());
  return result;
}
