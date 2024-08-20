#include "Helix.h"

namespace ctask {

  Vector3d Helix::operator()(float_t t) const noexcept
  {
    Vector3d v;
    float_t tcurr = t - this->getOffset();
    v.x = std::cos(tcurr) * radius_;
    v.y = std::sin(tcurr) * radius_;
    v.z = step_ * tcurr / (2.0 * kPi);
    return v;
  }

  Vector3d Helix::getDerivative(float_t t) const noexcept
  {
    Vector3d v;
    float_t tcurr = t - this->getOffset();
    v.x =-std::sin(tcurr) * radius_;
    v.y = std::cos(tcurr) * radius_;
    v.z = step_ / (2.0 * kPi);
    return v;
  }

  
}
