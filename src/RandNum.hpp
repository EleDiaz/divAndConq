#pragma once
#include <cstdlib>
#include <ctime>
#include "Counter.hpp"



class RandNum
{
private:
  unsigned int num;
public:
  static Counter counter;
  RandNum() {
    num = (rand() % 500);
  };
  RandNum(int i): num(i) {};
  virtual ~RandNum() {};
  operator int() const { return num;};
  bool operator==(const RandNum & other) {
    counter++;
    return other.num == num;
  };
  bool operator<(const RandNum & other) {
    counter++;
    return num < other.num;
  };
  bool operator>(const RandNum & other) {
    counter++;
    return num > other.num;
  };
  bool operator<=(const RandNum & other) {
    counter++;
    return num <= other.num;
  };
  bool operator>=(const RandNum & other) {
    counter++;
    return num >= other.num;
  };
  const RandNum operator*(const RandNum & other) {
    counter++;
    return num * other.num;
  };
  const RandNum operator-(const RandNum & other) {
    counter++;
    return num - other.num;
  };
  const RandNum operator+(const RandNum & other) {
    counter++;
    return num + other.num;
  };
};

