#ifndef ARC_H
#define ARC_H

#include <iostream>
#include "Cost.h"

enum class Transport_type {walking, biking, driving};

class Arc;

std::string transport_type_to_str(Transport_type t);
std::ostream& operator<<(std::ostream&, const class Arc&);

class Arc{

public:

  Cost cost;
  Transport_type type;

public:

  friend std::ostream& operator<<(std::ostream&, const Arc&);
};

#endif
