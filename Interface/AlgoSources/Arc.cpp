
#include "Arc.h"




std::string transport_type_to_str(Transport_type t){
  switch (t) {
    case Transport_type::walking:
      return "walking";
    case Transport_type::biking:
      return "biking";
    case Transport_type::driving:
      return "driving";
    default:
      return "not defined yet";
  }
  return "";
}

std::ostream& operator<<(std::ostream& os, const Arc& arc){
    os << "Arc for " << transport_type_to_str(arc.type) << " " << arc.cost;
    return os;
}
