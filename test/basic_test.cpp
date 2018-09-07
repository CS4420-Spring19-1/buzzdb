// BASIC TEST

#include <gtest/gtest.h>

#include "engine.h"

namespace engine {

TEST(BasicTest, Test1) {

    std::cout << "Square root:" << square_root(2500) << "\n";

    EXPECT_EQ(square_root(100), 10);

}

}  // End engine namespace
