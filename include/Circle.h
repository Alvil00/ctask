
#include "Ellipsis.h"

namespace ctask{
  
class Circle : public Ellipsis{
public:
  Circle() {}
  Circle(float_t radius, float_t t_offset=0.0) : Ellipsis(radius, radius, t_offset) {}
  Circle(Circle &&) = default;
  Circle(const Circle &) = default;
  Circle &operator=(Circle &&) = default;
  Circle &operator=(const Circle &) = default;

  float_t getRadius() const noexcept
  {
    return this->getXRatio();
  }
  
  ~Circle() override {}

};

}
