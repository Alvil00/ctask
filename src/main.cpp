#include "curves.h"
#include <memory>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <functional>
#include <iomanip>

using Curve = ctask::BaseCurve;
using CurvePtr = std::shared_ptr<Curve>;
using CirclePtr = std::shared_ptr<ctask::Circle>;
using ctask::Circle;
using ctask::Ellipsis;
using ctask::Helix;

enum class BuildCurveType : std::int32_t
{
  kEllipsis = 0,
  kCircle = 1,
  kHelix = 2
};

class RandomCurveBuilder
{
public:

  RandomCurveBuilder() 
    : rd(), gen(rd()), d({1,1,1}) ,
    radii_distr(2.0, 1.0), 
    step_distr(0.0, 1.0), 
    offset_distr(0.0, ctask::kQuaterPi),
    counter_(3)
  {
  }

  RandomCurveBuilder(ctask::float_t radii_expected, ctask::float_t radii_dispersion, ctask::float_t step_expected, ctask::float_t step_dispersion, ctask::float_t offset_expected, ctask::float_t offset_dispersion)
    : rd(), gen(rd()), d({1,1,1}) ,
    radii_distr(radii_expected * radii_expected / radii_dispersion, radii_dispersion / radii_expected), 
    step_distr(step_expected, step_dispersion), 
    offset_distr(offset_expected, offset_dispersion),
    counter_(3)
  {}

  std::unique_ptr<Curve> operator()(void) 
  {
    std::int32_t rand = d(gen);
    ++counter_.at(rand);
    auto build_type = static_cast<BuildCurveType>(rand);
    auto radii = radii_distr(gen);
    auto offset = offset_distr(gen);
    switch(build_type)
    {
      default:
      case BuildCurveType::kEllipsis:
        return std::make_unique<ctask::Ellipsis>(radii,radii_distr(gen), offset);
      case BuildCurveType::kCircle:
        return std::make_unique<ctask::Circle>(radii, offset);
      case BuildCurveType::kHelix:
        return std::make_unique<ctask::Helix>(radii, step_distr(gen), offset);
    }

  }

  const std::vector<std::int32_t>& get_stat() const noexcept
  {
    return counter_;
  }

private:
  std::random_device rd;
  std::mt19937 gen;
  std::discrete_distribution<std::int32_t> d;
  std::gamma_distribution<ctask::float_t> radii_distr;
  std::normal_distribution<ctask::float_t> step_distr;
  std::normal_distribution<ctask::float_t> offset_distr;
  std::vector<int32_t> counter_;

};

std::ostream& operator<<(std::ostream& os, const ctask::Vector3d& v ) {
        os << "x:" << std::setw(9) << v.x <<"  " << "y:" << std::setw(9) << v.y << "  " << "z:" << std::setw(9) << v.z << "  ";
        return os;
}

constexpr std::int32_t curves_num = 100;

std::int32_t main(std::int32_t argc, char** argv)
{
  RandomCurveBuilder rcb;
  std::vector<CurvePtr> curves;
  curves.reserve(curves_num);
  std::cout.setf(std::ios::fixed | std::ios::internal);

  std::cout << "Beginn of process random curves generation" << std::endl;
  for(std::int32_t i=0;i< curves_num;++i)
    curves.push_back(rcb());

  std::cout << "Builder has create"<< std::endl;
  std::cout << rcb.get_stat()[static_cast<std::int32_t>(BuildCurveType::kEllipsis)] << " ellipsis curves objects" << std::endl;
  auto circle_num = rcb.get_stat()[static_cast<std::int32_t>(BuildCurveType::kCircle)];
  std::cout << circle_num << " circle curves objects" << std::endl;
  std::cout << rcb.get_stat()[static_cast<std::int32_t>(BuildCurveType::kHelix)] << " helixes curves objects" << std::endl;
  std::cout << "Total count of created objects:" << curves_num << std::endl;

  constexpr ctask::float_t targ = ctask::kQuaterPi;  
  auto rprint = [targ](const CurvePtr& ptr){ std::cout << "Value: " <<(*ptr)(targ) << "Derivative: " << ptr->getDerivative(targ) <<std::endl;};
  std::cout << "Result of evaluation every curve and the derivative for t=π/4 argument" << std::endl;
  std::for_each(curves.cbegin(), curves.cend(), rprint);

  std::vector<CirclePtr> circles; 
  circles.reserve(circle_num);
  for(auto& c: curves)
  {
    if(CirclePtr cptr = dynamic_pointer_cast<Circle>(c))
      circles.push_back(cptr);
  }
  std::cout << circles.size() << " circles copied in the only-circle container" << std::endl;

  std::sort(circles.begin(), circles.end(),
      [](const auto& a, const auto& b){ return a->getRadius() < b->getRadius();});

  std::cout << "Min circle radii:" << circles.front()->getRadius()<< std::endl;
  std::cout << "Max circle radii:" << circles.back()->getRadius() << std::endl;

  ctask::float_t acc = std::reduce(circles.cbegin(), circles.cend(), 0.0,[](ctask::float_t t,const auto& c){return t+c->getRadius();});
  std::cout << "Sum of circle radius accumulator:" << acc << std::endl;



  return 0;
}
