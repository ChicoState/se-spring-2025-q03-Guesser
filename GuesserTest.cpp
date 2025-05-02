/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
// TEST(GuesserTest, smoke_test)
// {
//   Guesser object("Secret");
//   ASSERT_EQ( 1+1, 2 );
// }

TEST(GuesserTest, correct_first_try)
{
	Guesser object("Password");
	ASSERT_TRUE(object.match("Password"));
  	ASSERT_EQ( 3, object.remaining());
}

TEST(GuesserTest, correct_second_try)
{
	Guesser object("Password");
	object.match("password");
	object.match("Password");
  	ASSERT_EQ( 2, object.remaining());
}

TEST(GuesserTest, locked_test_after_3_tries)
{
	Guesser object("Secret");
	object.match("secret");
	object.match("secrets");
	object.match("secretS");
	ASSERT_FALSE(object.match("Secret")); //should be false since locked
  	ASSERT_EQ( 0, object.remaining());
}

TEST(GuesserTest, more_than_32_chars)
{
	Guesser object("thisisasentencewithmorethan32characterstofillinthespaceandtotestifitonlychecksthefirst32characters");
	ASSERT_TRUE(object.match("thisisasentencewithmorethan32char"));
  	ASSERT_EQ( 3, object.remaining());
}

TEST(GuesserTest, brute_force)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("bruteforce"));
	ASSERT_FALSE(object.match("Password")); //should be locked
  	ASSERT_EQ( 2, object.remaining());
}

TEST(GuesserTest, reset_counter_test)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("Passwords"));
	ASSERT_TRUE(object.match("Password")); 
  	ASSERT_EQ( 3, object.remaining()); //should reset to 3 if password is correct
}

TEST(GuesserTest, blank_input)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match(""));
	ASSERT_FALSE(object.match("Password")); 
  	ASSERT_EQ(2, object.remaining()); //locked due to blank input
}