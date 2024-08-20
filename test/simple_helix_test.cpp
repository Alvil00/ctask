#include "gtest/gtest.h"
#include "Helix.h"
#include <memory>
#include <vector>

namespace {

class HelixFixture : public testing::Test
{
  public:
    static void SetUpTestSuite()
    {
        h = std::make_unique<std::vector<ctask::Helix>>();
        h->emplace_back(8.0, -2.0);
        h->emplace_back(8.0, -2.0, ctask::kQuaterPi);
    }

    static std::unique_ptr<std::vector<ctask::Helix>> h;

    static constexpr ctask::float_t test_t_value = 3.0*ctask::kHalfPi;
    static constexpr ctask::float_t eps = std::numeric_limits<ctask::float_t>::epsilon() * 1e2;
};

std::unique_ptr<std::vector<ctask::Helix>> HelixFixture::h = nullptr;
TEST_F(HelixFixture, HelixSimpleTest)
{
  auto v = h->at(0)(test_t_value);
  auto d = h->at(0).getDerivative(test_t_value);
  EXPECT_NEAR(v.x, 0.0, eps);
  EXPECT_NEAR(v.y,-8.0, eps);
  EXPECT_NEAR(v.z,-1.5, eps);
  EXPECT_NEAR(d.x, 8.0, eps);
  EXPECT_NEAR(d.y, 0.0, eps);
  EXPECT_NEAR(d.z,-1.0 / ctask::kPi , eps);
}

TEST_F(HelixFixture, HelixSimpleTest1)
{
  auto v = h->at(1)(test_t_value);
  auto d = h->at(1).getDerivative(test_t_value);
  EXPECT_NEAR(v.x,-4.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(v.y,-4.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(v.z,-1.25, eps);
  EXPECT_NEAR(d.x, 4.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(d.y,-4.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(d.z,-1.0 / ctask::kPi, eps);
}

}
