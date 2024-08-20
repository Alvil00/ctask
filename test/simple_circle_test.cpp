#include "gtest/gtest.h"
#include "Circle.h"
#include <memory>
#include <vector>

namespace {

class CircleFixture : public testing::Test
{
  public:
    static void SetUpTestSuite()
    {
        c = std::make_unique<std::vector<ctask::Circle>>();
        c->emplace_back(2.0);
        c->emplace_back(2.0, ctask::kQuaterPi);
    }

    static std::unique_ptr<std::vector<ctask::Circle>> c;

    static constexpr ctask::float_t test_t_value = ctask::kPi;
    static constexpr ctask::float_t eps = std::numeric_limits<ctask::float_t>::epsilon() * 1e2;
};

std::unique_ptr<std::vector<ctask::Circle>> CircleFixture::c = nullptr;
TEST_F(CircleFixture, CircleSimpleTest)
{
  auto v = c->at(0)(test_t_value);
  auto d = c->at(0).getDerivative(test_t_value);
  EXPECT_NEAR(v.x,-2.0, eps);
  EXPECT_NEAR(v.y, 0.0, eps);
  EXPECT_NEAR(v.z, 0.0, eps);
  EXPECT_NEAR(d.x, 0.0, eps);
  EXPECT_NEAR(d.y,-2.0, eps);
  EXPECT_NEAR(d.z, 0.0, eps);
}

TEST_F(CircleFixture, CircleSimpleTest1)
{
  auto v = c->at(1)(test_t_value);
  auto d = c->at(1).getDerivative(test_t_value);
  EXPECT_NEAR(v.x,-1.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(v.y, 1.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(v.z, 0.0, eps);
  EXPECT_NEAR(d.x,-1.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(d.y,-1.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(d.z, 0.0, eps);
}

}
