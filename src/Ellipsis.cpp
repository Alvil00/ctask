#include "Ellipsis.h"

namespace ctask {
  
  Vector3d Ellipsis::operator()(float_t t) const 
  {
    Vector3d v;
    float_t tcurr = t - this->getOffset();
    v.x = std::cos(tcurr) * a_; 
    v.y = std::sin(tcurr) * b_; 
    return v; 
  }

  Vector3d Ellipsis::getDerivative(float_t t) const 
  {
    Vector3d v;
    float_t tcurr = t - this->getOffset();
    v.x = -std::sin(tcurr) * a_;
    v.y = std::cos(tcurr) * b_;
    return v;
  }
}
