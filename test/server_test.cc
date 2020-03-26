#include <cstring>
#include <vector>

// #include <grpcpp/impl/grpc_library.h>
#include <gtest/gtest.h>

int Factorial(int n);  // Returns the factorial of n


// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(Factorial(0), 1);
}



// int main(int argc, char** argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }


int Factorial(int n) {
	return n +1;
}
