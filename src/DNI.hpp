#pragma once
#include <cstdlib>
#include <ctime>
#include "Counter.hpp"

class DNI
{
private:
    unsigned int num;
public:
    static Counter counter;
    DNI() {
        num = 30000000 + (rand() % 50000000);
    };
    DNI(int i): num(i) {};
    virtual ~DNI() {};
    operator int() const { return num;};
    bool operator==(const DNI & dni) {
        counter++;
        return dni.num == num;
    };
    bool operator<(const DNI & dni) {
        counter++;
        return num < dni.num;
    };
    bool operator>(const DNI & dni) {
        counter++;
        return num > dni.num;
    };
    bool operator<=(const DNI & dni) {
        counter++;
        return num <= dni.num;
    };
    bool operator>=(const DNI & dni) {
        counter++;
        return num >= dni.num;
    };
};
