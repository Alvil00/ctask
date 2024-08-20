#ifndef __CTASK__BASE_CURVE_H__
#define __CTASK__BASE_CURVE_H__

#include "base.h"

namespace ctask{

namespace exceptions {
  
class CurveException: public std::exception
{
public:
  explicit CurveException(const char* message)
        : msg_(message) {}

  explicit CurveException(const std::string& message)
        : msg_(message) {}

  virtual ~CurveException() {}

  virtual const char* what() const noexcept {
       return msg_.c_str();
    }

protected:
    std::string msg_;
};

}

class BaseCurve {
public:
  BaseCurve(){}
  explicit BaseCurve(float_t t_offset) : t_offset_(t_offset){
    if(!std::isfinite(t_offset))
      throw exceptions::CurveException {"Parameter offset value must be finite"};
  }

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
