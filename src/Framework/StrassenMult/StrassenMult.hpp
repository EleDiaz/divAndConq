#pragma once
#include <iostream>
#include <tuple>
#include "../Framework.hpp"
#include "Matrix.hpp"

typedef int VAL;

class StrassenData : public Matrix, public Problem, public Solution {
  // Se trata de una mult debes guardar las dos matrices para calcular si
  // es el caso mínimo
};


class StrassenMult : public DivAndConquer<StrassenData, StrassenData> {
private:
  StrassenData combine(StrassenData p, vector<StrassenData> ss);

  bool isSimple(StrassenData p);

  StrassenData simplySolve(StrassenData p);

  vector<StrassenData *> decompose(StrassenData p);

public:
  StrassenMult() {};
};

bool StrassenMult::isSimple(StrassenData data) {
  return (data.getM() == 2 && data.getN() == 2);
}

StrassenData StrassenMult::simplySolve(StrassenData data) {
  // TODO Que coño pongo aqui ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ^
  data.get(i, j);
  return data;
}

StrassenData StrassenMult::combine(StrassenData p, vector<StrassenData> ss) {
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
  cout << "join  " << vec << endl;
  return StrassenData(pair<int, int> {xs.first,ys.second}, &vec);
}

vector<StrassenData *> StrassenMult::decompose(StrassenData data) {
  cout << "decompose  " << *data.getVec() << endl;
  int middle = data.getXs().first + (data.getXs().second - data.getXs().first) / 2;
  cout << "en " << data.getXs().first << " y " << middle << endl;
  cout << "en " << middle+1 << " y " << data.getXs().second << endl;
  vector<StrassenData *> result(2);
  result[0] = new StrassenData(pair<int, int> {data.getXs().first, middle}, data.getVec());
  result[1] = new StrassenData(pair<int, int> {middle+1, data.getXs().second}, data.getVec());
  return result;
}
