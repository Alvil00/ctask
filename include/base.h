#ifndef __CTASK__BASE_H__
#define __CTASK__BASE_H__
#include <limits>
#include <exception>
#include <string>
#include <numbers>
#include <cmath>

namespace ctask {

using float_t = double;

struct Vector3d{
  float_t x;
  float_t y;
  float_t z;
};

constexpr float_t kPi = std::numbers::pi_v<float_t>;
constexpr float_t kHalfPi = kPi / 2.0;
constexpr float_t kQuaterPi = kPi / 4.0;

}
#endif
