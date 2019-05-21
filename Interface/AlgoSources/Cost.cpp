
#include "Cost.h"


Cost::Cost(){
  distance = 0;
  height_diff = 0;
  co2 = 0;
  effort = 0;
  time = 0;
  price = 0.0;
  k = 0;
}

// Cost::Cost(double a, double b, unsigned long long t, double p){
//   distance = a;
//   height_diff = b;
//   time = t;
//   price = p;
// }
//
// Cost::Cost(double a, double b){
//   distance = a;
//   height_diff = b;
//   time = 0;
//   price = 0.0;
// }

bool operator<(const Cost& cost1, const Cost& cost2){
  return (cost1.k <= cost2.k) && (cost1.distance <= cost2.distance) && (cost1.height_diff <= cost2.height_diff) && (cost1.time <= cost2.time) && (cost1.co2 <= cost2.co2) && (cost1.effort <= cost2.effort) && (cost1.price <= cost2.price) && (cost1 != cost2);
}

bool operator==(const Cost& cost1, const Cost& cost2){
  return (cost1.k == cost2.k) && (cost1.distance == cost2.distance) && (cost1.height_diff == cost2.height_diff) && (cost1.time == cost2.time) && (cost1.co2 == cost2.co2) && (cost1.effort == cost2.effort) && (cost1.price == cost2.price);
}

bool operator<=(const Cost& cost1, const Cost& cost2){
  return !(cost1 > cost2);
}

bool operator>=(const Cost& cost1, const Cost& cost2){
  return !(cost1 < cost2);
}

bool operator>(const Cost& cost1, const Cost& cost2){
  return (cost1.k >= cost2.k) && (cost1.distance >= cost2.distance) && (cost1.height_diff >= cost2.height_diff) && (cost1.time >= cost2.time) && (cost1.co2 >= cost2.co2) && (cost1.effort >= cost2.effort) && (cost1.price >= cost2.price) && (cost1 != cost2);
}

bool operator!=(const Cost& cost1, const Cost& cost2){
  return !(cost1 == cost2);
}

Cost operator+(const Cost& cost1, const Cost& cost2){
  Cost res;
  res.distance = cost1.distance + cost2.distance;
  res.height_diff = cost1.height_diff + cost2.height_diff;
  res.effort = cost1.effort + cost2.effort;
  res.co2 = cost1.co2 + cost2.co2;
  res.time = cost1.time + cost2.time;
  res.price = cost1.price + cost2.price;
  res.k = cost1.k + cost2.k;
  return res;
}

std::ostream& operator<<(std::ostream& os, const Cost& cost){
    os << "(" << cost.distance << ", " << cost.height_diff << ", " << cost.effort << ", " << cost.co2 << ")";
    os << "(" << cost.time << ", " << cost.price << ", " << cost.k << ")";
    return os;
}
