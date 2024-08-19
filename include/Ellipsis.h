#ifndef __CTASK__ELLIPSIS_H__
#define __CTASK__ELLIPSIS_H__

#include "BaseCurve.h"


namespace ctask {

class Ellipsis : public BaseCurve {
public:
  Ellipsis() : BaseCurve() {}
  Ellipsis(float_t x_ratio, float_t y_ratio, float_t t_offset=0.0) : BaseCurve(t_offset), a_(x_ratio), b_(y_ratio)
  {
    if(x_ratio == 0.0  || y_ratio == 0.0)
        throw std::exception {};
  }
  Ellipsis(Ellipsis &&) = default;
  Ellipsis(const Ellipsis &) = default;
  Ellipsis &operator=(Ellipsis &&) = default;
  Ellipsis &operator=(const Ellipsis &) = default;
  ~Ellipsis() override {}

  Vector3d operator()(float_t t) const override;
  Vector3d getDerivative(float_t t) const override;

  float_t getXRratio() const noexcept
  {
    return a_;
  }

  float_t getYRatio() const noexcept
  {
    return b_;
  }

private:
  float_t a_ {1.0}; // x ratio
  float_t b_ {1.0}; // y ratio
  
};

}
#endif // !__CTASK__ELLIPSIS_H__
