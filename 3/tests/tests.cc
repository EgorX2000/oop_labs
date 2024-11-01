#include <gtest\gtest.h>

#include "../figures/Figures.h"

TEST(compareSuite, baseCase) {
    Octagon oct1{{0, 0}, 1};
    Triangle tri1{{0, 0}, 1};
    Square sqr1{{0, 0}, 1};

    Octagon oct2{{0, 0}, 1};
    Triangle tri2{{0, 0}, 1};
    Square sqr2{{0, 0}, 1};

    ASSERT_TRUE(oct1 == oct2 && tri1 == tri2 && sqr1 == sqr2);
}

TEST(compareSuite, failOnDifferentPoints) {
    Octagon oct1{{0, 0}, 1};
    Triangle tri1{{0, 0}, 1};
    Square sqr1{{0, 0}, 1};

    Octagon oct2{{1, 1}, 1};
    Triangle tri2{{1, 1}, 1};
    Square sqr2{{1, 1}, 1};

    ASSERT_FALSE(oct1 == oct2 || tri1 == tri2 || sqr1 == sqr2);
}

TEST(areaCalculationSuite, baseCaseOct) {
    double answer = 4.8284271247461898;
    Octagon oct{{0, 0}, 1};
    ASSERT_EQ(double(oct), answer);
}

TEST(areaCalculationSuite, baseCaseTri) {
    double answer = 0.4330127018922193;
    Triangle tri{{0, 0}, 1};
    ASSERT_EQ(double(tri), answer);
}

TEST(areaCalculationSuite, baseCaseSqr) {
    double answer = 1;
    Square sqr{{0, 0}, 1};
    ASSERT_EQ(double(sqr), answer);
}

TEST(centerCalculationSuite, baseCaseOct) {
    Vertex answer;
    answer.x = 1.2071067811865475;
    answer.y = 0.5;
    Octagon oct{{0, 0}, 1};
    ASSERT_EQ(oct.GetCenter().x, answer.x);
    ASSERT_EQ(oct.GetCenter().y, answer.y);
}

TEST(centerCalculationSuite, baseCaseTri) {
    Vertex answer;
    answer.x = 0.5;
    answer.y = 0.28867513459481287;
    Triangle tri{{0, 0}, 1};
    ASSERT_EQ(tri.GetCenter().x, answer.x);
    ASSERT_EQ(tri.GetCenter().y, answer.y);
}

TEST(centerCalculationSuite, baseCaseSqr) {
    Vertex answer;
    answer.x = 0.5;
    answer.y = 0.5;
    Square sqr{{0, 0}, 1};
    ASSERT_EQ(sqr.GetCenter().x, answer.x);
    ASSERT_EQ(sqr.GetCenter().y, answer.y);
}