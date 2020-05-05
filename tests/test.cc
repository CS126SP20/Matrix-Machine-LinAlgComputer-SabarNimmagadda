// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <Linear Algebra/computations.h>
#include <Eigen/Dense>



TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("Computation tests") {
    Eigen::Matrix3d test_mat;
    test_mat << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    Eigen::Matrix3d test_mat2;
    test_mat2 << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    std::stringstream ss;
    std::stringstream os;

    SECTION("RREF") {
        REQUIRE(Computations::ComputeRREF(test_mat).size() == test_mat.size());
    }
    SECTION("Permutations") {
        REQUIRE(Computations::ComputePermutationMatrix(test_mat).size() == test_mat.size());
    }
    SECTION("Multiplication") {
        REQUIRE(Computations::ComputeDotProduct(test_mat, test_mat2, 3) == 285);
    }
    SECTION("Determinant") {
        REQUIRE(Computations::ComputeDeterminant(test_mat) == 0);
    }
    SECTION("Matrix Content") {
        ss << test_mat;
        std::string str = "1 2 3\n"
                          "4 5 6\n"
                          "7 8 9";
        REQUIRE(ss.str() == str);
    }
    SECTION("Multiplication Size") {
        REQUIRE(Computations::ComputeMultiply(test_mat, test_mat2).size() == 9);
    }
}