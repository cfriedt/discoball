#include "gtest/gtest.h"
#include "strlen.h"

TEST( StrlenTest, Zero ) {
  EXPECT_EQ( 0, strlen( "" ) );
}
