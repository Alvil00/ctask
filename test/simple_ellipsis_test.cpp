#include "gtest/gtest.h"
#include "Ellipsis.h"
#include <memory>
#include <vector>

namespace {

class EllipsisFixture : public testing::Test
{
  public:
    static void SetUpTestSuite()
    {
        e = std::make_unique<std::vector<ctask::Ellipsis>>();
        e->emplace_back(2.0, 4.0);
        e->emplace_back(2.0, 4.0, ctask::kQuaterPi);
    }

    static std::unique_ptr<std::vector<ctask::Ellipsis>> e;

    static constexpr ctask::float_t test_t_value = ctask::kHalfPi;
    static constexpr ctask::float_t eps = std::numeric_limits<ctask::float_t>::epsilon() * 1e2;
};

std::unique_ptr<std::vector<ctask::Ellipsis>> EllipsisFixture::e = nullptr;

TEST_F(EllipsisFixture, EllipsisSimpleTest)
{
  auto v = e->at(0)(test_t_value);
  auto d = e->at(0).getDerivative(test_t_value);
  EXPECT_NEAR(v.x, 0.0, eps);
  EXPECT_NEAR(v.y, 4.0, eps);
  EXPECT_NEAR(v.z, 0.0, eps);
  EXPECT_NEAR(d.x,-2.0, eps);
  EXPECT_NEAR(d.y, 0.0, eps);
  EXPECT_NEAR(d.z, 0.0, eps);
}

TEST_F(EllipsisFixture, EllipsisSimpleTest1)
{
  auto v = e->at(1)(test_t_value);
  auto d = e->at(1).getDerivative(test_t_value);
  EXPECT_NEAR(v.x, 1.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(v.y, 2.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(v.z, 0.0, eps);
  EXPECT_NEAR(d.x,-1.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(d.y, 2.0*std::numbers::sqrt2_v<ctask::float_t>, eps);
  EXPECT_NEAR(d.z, 0.0, eps);
}

TEST(EllipsisCrashTest, EllipsisCrashTest)
{
  constexpr ctask::float_t inf = std::numeric_limits<ctask::float_t>::infinity();
  constexpr ctask::float_t nan = std::numeric_limits<ctask::float_t>::quiet_NaN();

  EXPECT_THROW((ctask::Ellipsis{inf, 3.0}), ctask::exceptions::CurveException);
  EXPECT_THROW((ctask::Ellipsis{3.0, inf}), ctask::exceptions::CurveException);
  EXPECT_THROW((ctask::Ellipsis{3.0, 1.0, inf}), ctask::exceptions::CurveException);

  EXPECT_THROW((ctask::Ellipsis{nan, 3.0}), ctask::exceptions::CurveException);
  EXPECT_THROW((ctask::Ellipsis{3.0, nan}), ctask::exceptions::CurveException);
  EXPECT_THROW((ctask::Ellipsis{3.0, 1.0, nan}), ctask::exceptions::CurveException);

  EXPECT_THROW((ctask::Ellipsis{-1.0, 3.0}), ctask::exceptions::CurveException);
  EXPECT_THROW((ctask::Ellipsis{3.0, -1.0}), ctask::exceptions::CurveException);
  EXPECT_NO_THROW((ctask::Ellipsis{3.0, 2.0, -1.0}));
}

}
