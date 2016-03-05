#include "Ordering.hpp"

template <class VAL>
class QuickSort : public Ordering<VAL>
{
private:
  int split(Vector<VAL> & vec, int first, int second);
  void quickSort(Vector<VAL> & vec, int left, int right);
public:
  QuickSort(): Ordering<VAL>("QuickSort") {};
  void sort(Vector<VAL> & vec);
};


template <class VAL>
int QuickSort<VAL>::split(Vector<VAL> & vec, int first, int last) {
    int izq, dch;
    VAL val_pivote = vec[first];
    izq = first + 1;
    dch = last;
    do {
        while ((izq <= dch) && (vec[izq] <= val_pivote)) izq++;
        while ((izq <= dch) && (vec[dch] >= val_pivote)) dch--;
        if (izq<dch) {
            vec.swap(izq, dch);
            dch--; izq++;
        }
    } while (izq <= dch);
    vec.swap(first, dch);
    trace("Valor Pivote: " << val_pivote << ": " << vec << endl);
    return dch;
}

template <class VAL>
void QuickSort<VAL>::quickSort(Vector<VAL> & vec, int left, int right) {
  int posPivot;
  if (left < right) {
    posPivot = split(vec, left, right);
    quickSort(vec, left, posPivot-1);
    quickSort(vec, posPivot+1, right);
  }
}

template <class VAL>
void QuickSort<VAL>::sort(Vector<VAL> & vec) {
  quickSort(vec, 0, vec.getSize()-1);
}
