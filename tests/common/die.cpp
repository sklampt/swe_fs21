#include <string>
#include "gtest/gtest.h"
#include "common/game/Die.h"

class DieTest : public ::testing::Test{
protected:
    Die* die = new Die(Color::green);
};

TEST_F(DieTest, Die_Constructor)
{
    EXPECT_EQ(die->get_face(), Face::undefined);
    EXPECT_EQ(die->get_color(), Color::green);
}

TEST_F(DieTest, Die_Throw_Dice) {
    Face face = die->throw_die();
    ASSERT_NE(face, Face::undefined);
}

TEST_F(DieTest, Die_Colors){
    std::string color = die->get_color_as_string();
    std::string expected_color = "green";
    ASSERT_EQ(color, expected_color);
}