#ifndef __CTASK__HELIX_H__
#define __CTASK__HELIX_H__
#include "BaseCurve.h"

namespace ctask {
  
  class Helix : public BaseCurve {
  public:
    Helix(){}
    Helix(float_t radius, float_t step, float_t t_offset=0.0) : BaseCurve(t_offset), radius_(radius), step_(step) {
      if(radius_ <= 0.0)
        throw exceptions::CurveException {"The radii of curve must be greater than zero"};
      if(!std::isfinite(radius_))
        throw exceptions::CurveException {"The radii value must be finite"};
      if(!std::isfinite(step_))
        throw exceptions::CurveException {"The step value must be finite"};
    }
    Helix(Helix &&) = default;
    Helix(const Helix &) = default;
    Helix &operator=(Helix &&) = default;
    Helix &operator=(const Helix &) = default;
    ~Helix() override {}

    Vector3d operator()(float_t) const noexcept override;
    Vector3d getDerivative(float_t) const noexcept override;

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
