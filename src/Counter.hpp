#pragma once
#include <limits>

class Counter
{
private:
    int accum;
    int max;
    int min;
    int localAccum;
public:
    Counter(){
        reset();
    };
    void start() {
        localAccum = 0;
    };
    int stop() {
        min = localAccum < min? localAccum:min;
        max = localAccum > max? localAccum:max;
        accum += localAccum;
        return localAccum;
    };
    void reset(void) {
        min = std::numeric_limits<int>::max();
        max = 0;
        accum = 0;
    }
    
    Counter& operator++(int) {
        localAccum++;
        return *this;
    };
    int getAccum() { return accum; };
    int getMax() { return max; };
    int getMin() { return min; };
};
