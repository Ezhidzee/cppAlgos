#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <vector>
#include <list>

#include "ezhidzeAlgorithm.hpp"
#include "xrange.hpp"
#include "zip.hpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

struct city {
    std::string name;

    int population;
};

std::vector<int> v = {2, 4, 6, 8};
std::vector<city> v1 = {city("Name1", 123), city("Name2", 456), city("Name3", 789)};

TEST(ezhidzeAlgorithm, all_of) {
    EXPECT_EQ(ezhidze::all_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), true);
    v[0] = 1;
    EXPECT_EQ(ezhidze::all_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), false);

    EXPECT_EQ(ezhidze::all_of(v1.begin(), v1.end(), [](city &x) { return x.population < 1000; }), true);
    v1 = {city("Name1", 123), city("Name2", 456), city("Name3", 1007)};
    EXPECT_EQ(ezhidze::all_of(v1.begin(), v1.end(), [](city &x) { return x.population < 1000; }), false);
}

TEST(ezhidzeAlgorithm, any_of) {
    v = {1, 2, 3, 5};
    EXPECT_EQ(ezhidze::any_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), true);
    v = {1, 1, 3, 5};
    EXPECT_EQ(ezhidze::any_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), false);
}

TEST(ezhidzeAlgorithm, none_of) {
    v = {1, 1, 3, 5};
    EXPECT_EQ(ezhidze::none_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), true);
    v = {1, 2, 3, 5};
    EXPECT_EQ(ezhidze::none_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), false);
}

TEST(ezhidzeAlgorithm, one_of) {
    v = {1, 2, 3, 5};
    EXPECT_EQ(ezhidze::one_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), true);
    v = {1, 2, 4, 5};
    EXPECT_EQ(ezhidze::one_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), false);
    v = {1, 1, 3, 5};
    EXPECT_EQ(ezhidze::one_of(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), false);
}

TEST(ezhidzeAlgorithm, is_sorted) {
    v = {1, 1, 3, 5};
    EXPECT_EQ(ezhidze::is_sorted(v.begin(), v.end()), true);
    v = {1, 2, 8, 5};
    EXPECT_EQ(ezhidze::is_sorted(v.begin(), v.end()), false);

    v1 = {city("Name1", 123), city("Name2", 456), city("Name3", 789)};
    EXPECT_EQ(ezhidze::is_sorted(v1.begin(), v1.end(), [](city &a, city &b) { return a.population < b.population; }),
              true);
    v1 = {city("Name1", 123), city("Name2", 156654), city("Name3", 789)};
    EXPECT_EQ(ezhidze::is_sorted(v1.begin(), v1.end(), [](city &a, city &b) { return a.population < b.population; }),
              false);
}

TEST(ezhidzeAlgorithm, is_partitioned) {
    v = {2, 4, 5, 7};
    EXPECT_EQ(ezhidze::is_partitioned(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), true);
    v = {2, 4, 5, 6};
    EXPECT_EQ(ezhidze::is_partitioned(v.begin(), v.end(), [](int x) { return x % 2 == 0; }), false);
}

TEST(ezhidzeAlgorithm, find_not) {
    v = {2, 2, 2, 7};
    EXPECT_EQ(ezhidze::find_not(v.begin(), v.end(), 2), v.begin() + 3);
}

TEST(ezhidzeAlgorithm, find_backward) {
    v = {2, 2, 2, 7};
    EXPECT_EQ(ezhidze::find_backward(v.begin(), v.end(), 2), v.begin() + 2);
}

TEST(ezhidzeAlgorithm, is_palindrome) {
    std::string str = "amogusugoma";
    EXPECT_EQ(ezhidze::is_palindrome(str.begin(), str.end()), true);
    str = "amogususgoma";
    EXPECT_EQ(ezhidze::is_palindrome(str.begin(), str.end()), false);

    v1 = {city("Name1", 123), city("Name2", 456), city("Name3", 123)};
    EXPECT_EQ(
            ezhidze::is_palindrome(v1.begin(), v1.end(), [](city &a, city &b) { return a.population == b.population; }),
            true);
}

TEST(xrange, xrange) {
    xrange<double> x(1.5, 5.5);
    std::vector<double> v2{x.begin(), x.end()};
    ASSERT_THAT(v2, testing::ElementsAre(1.5, 2.5, 3.5, 4.5));

    xrange<int> x1(4);
    std::vector<int> v3{x1.begin(), x1.end()};
    ASSERT_THAT(v3, testing::ElementsAre(0, 1, 2, 3));

    xrange<double> x2(1.5, 5.5, 0.5);
    std::vector<double> v4{x2.begin(), x2.end()};
    ASSERT_THAT(v4, testing::ElementsAre(1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5));
}

TEST(zip, zip) {
    std::list l = {1, 2, 3, 4, 5};
    std::vector v2 = {'a', 'b', 'c', 'd'};
    zip z(l, v2);
    std::vector v3(z.begin(), z.end());
    ASSERT_THAT(v3, testing::ElementsAre(std::pair{1, 'a'}, std::pair{2, 'b'}, std::pair{3, 'c'}, std::pair{4, 'd'}));
}