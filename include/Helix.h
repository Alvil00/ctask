#ifndef __CTASK__HELIX_H__
#define __CTASK__HELIX_H__
#include "BaseCurve.h"

namespace ctask {
  
  class Helix : public BaseCurve {
  public:
    Helix(){}
    Helix(float_t radius, float_t step, float_t t_offset=0.0) : BaseCurve(t_offset), radius_(radius), step_(step) {}
    Helix(Helix &&) = default;
    Helix(const Helix &) = default;
    Helix &operator=(Helix &&) = default;
    Helix &operator=(const Helix &) = default;
    ~Helix() override {}

    Vector3d operator()(float_t) const override;
    Vector3d getDerivative(float_t) const override;

    float_t getRadius() const noexcept
    {
      return radius_;
    }
    float_t getStepSize() const noexcept
    {
      return step_;
    }

  private:
    float_t radius_{1.0};
    float_t step_{ kPi};
    
  };
}

#endif  
