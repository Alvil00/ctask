#ifndef __CTASK__BASE_CURVE_H__
#define __CTASK__BASE_CURVE_H__

#include "base.h"

namespace ctask{

class BaseCurve {
public:
  BaseCurve(){}
  explicit BaseCurve(float_t t_offset) : t_offset_(t_offset){}
  BaseCurve(BaseCurve &&) = default;
  BaseCurve(const BaseCurve &) = default;
  BaseCurve &operator=(BaseCurve &&) = default;
  BaseCurve &operator=(const BaseCurve &) = default;

  virtual Vector3d operator()(float_t t) const=0;
  virtual Vector3d getDerivative(float_t t) const=0;

  virtual ~BaseCurve() {}

  float_t getOffset() const noexcept
  {
    return t_offset_;
  }

private:
  float_t t_offset_{ 0.0 }; 
};


}
#endif
