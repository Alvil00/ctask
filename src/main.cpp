//! The ctask programm makes several things as written in technical requirements
//  1. Create set of curves with random parameter distribution
//  2. Calculate each curves value and derivative in π/4 point
//  3. Create separate vector contains circles only 
//  4. Sort the vector by circle radius from the least to the greatest
//  5. Calculate the sum of circles radii by OpenMP tools

#include "curves.h"
#include <memory>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <functional>
#include <iomanip>
#ifdef PARALELL
#include "omp.h"
#endif

// Aliases
using Curve = ctask::BaseCurve;
using CurvePtr = std::shared_ptr<Curve>;
using CirclePtr = std::shared_ptr<ctask::Circle>;
using ctask::Circle;
using ctask::Ellipsis;
using ctask::Helix;

// Enumeration for all kinds of curves
enum class BuildCurveType : std::int32_t
{
  kEllipsis = 0,
  kCircle = 1,
  kHelix = 2
};

constexpr std::int32_t kNumberOfCurvesTypes = 3;

// Curve Builder Class
class RandomCurveBuilder
{
public:

  RandomCurveBuilder() 
    : rd(), gen(rd()), d({1,1,1}) ,
    radii_distr(2.0, 1.0), 
    step_distr(0.0, 1.0), 
    offset_distr(0.0, ctask::kQuaterPi),
    counter_(kNumberOfCurvesTypes)
  {
  }

  RandomCurveBuilder(ctask::float_t radii_expected, ctask::float_t radii_dispersion, ctask::float_t step_expected, ctask::float_t step_dispersion, ctask::float_t offset_expected, ctask::float_t offset_dispersion)
    : rd(), gen(rd()), d({1,1,1}) ,
    radii_distr(radii_expected * radii_expected / radii_dispersion, radii_dispersion / radii_expected), 
    step_distr(step_expected, step_dispersion), 
    offset_distr(offset_expected, offset_dispersion),
    counter_(kNumberOfCurvesTypes)
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
  std::gamma_distribution<ctask::float_t> radii_distr; // We need some always positive random distribution so i choose a gamma_distribution for this purpose
  std::normal_distribution<ctask::float_t> step_distr;
  std::normal_distribution<ctask::float_t> offset_distr;
  std::vector<int32_t> counter_;

};

// Vector3d stream output function
std::ostream& operator<<(std::ostream& os, const ctask::Vector3d& v ) {
        os << "x:" << std::setw(9) << v.x <<"  " << "y:" << std::setw(9) << v.y << "  " << "z:" << std::setw(9) << v.z << "  ";
        return os;
}

// Number of curves for creation
constexpr std::int32_t kCurvesNumber = 100000;

// Main function
std::int32_t main(std::int32_t argc, char** argv)
{
  // Crete builder of curves
  RandomCurveBuilder rcb;

  // Create curves vector
  std::vector<CurvePtr> curves;
  // Reserve the necessary space to avoid memory reallocation
  curves.reserve(kCurvesNumber);

  // Set float point output values flags
  std::cout.setf(std::ios::fixed | std::ios::internal);

  // Fill the vector
  std::cout << "Begin of process random curves generation" << std::endl;
  for(std::int32_t i=0;i< kCurvesNumber;++i)
    curves.push_back(rcb());

  // Print the hist statistic of created curves
  std::cout << "Builder has create"<< std::endl;
  std::cout << rcb.get_stat()[static_cast<std::int32_t>(BuildCurveType::kEllipsis)] << " ellipsis curves objects" << std::endl;
  auto circle_num = rcb.get_stat()[static_cast<std::int32_t>(BuildCurveType::kCircle)];
  std::cout << circle_num << " circle curves objects" << std::endl;
  std::cout << rcb.get_stat()[static_cast<std::int32_t>(BuildCurveType::kHelix)] << " helixes curves objects" << std::endl;
  std::cout << "Total count of created objects:" << kCurvesNumber << std::endl;

  // Evaluate and print the value and the derivative of each curve in corresponding point
  constexpr ctask::float_t targ = ctask::kQuaterPi;  
  auto rprint = [](const CurvePtr& ptr){ std::cout << "Value: " <<(*ptr)(targ) << "Derivative: " << ptr->getDerivative(targ) <<std::endl;};
  std::cout << "Result of evaluation every curve and the derivative for t=π/4 argument" << std::endl;
  std::for_each(curves.cbegin(), curves.cend(), rprint);

  // Create separate vector for circles and reserve space to avoid memory reallocation
  std::vector<CirclePtr> circles; 
  circles.reserve(circle_num);

  // Share every circle casted pointer 
  for(auto& c: curves)
  {
    if(CirclePtr cptr = dynamic_pointer_cast<Circle>(c))
      circles.push_back(cptr);
  }
  std::cout << circles.size() << " circles copied in the only-circle container" << std::endl;

  // Sort the vector
  std::sort(circles.begin(), circles.end(),
      [](const auto& a, const auto& b){ return a->getRadius() < b->getRadius();});

  std::cout << "Min circle radii:" << circles.front()->getRadius()<< std::endl;
  std::cout << "Max circle radii:" << circles.back()->getRadius() << std::endl;

  // Sum the radius of the vector
  ctask::float_t acc = 0.0;
  #ifndef PARALELL
  acc = std::reduce(circles.cbegin(), circles.cend(), 0.0,[](ctask::float_t t,const auto& c){return t+c->getRadius();});
  #else // PARALELL
  #pragma omp parallel
  {
    if(omp_get_thread_num() == 0)
      std::cout << "Run OpenMP parallel with " << omp_get_num_threads( ) << " threads" << std::endl;
    #pragma omp for reduction(+:acc)
    for (const auto& c: circles)
      acc += c->getRadius(); 
  }
  #endif
  std::cout << "Sum of circle radius accumulator:" << acc << std::endl;

  return 0;
}
