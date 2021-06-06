#include "gtest/gtest.h"
#include "common/game/Turn.h"

class TurnTest : public ::testing::Test{
protected:
    Turn* turn = new Turn();
};

TEST_F(TurnTest, Turn_Constructor)
{
    EXPECT_EQ(turn->getBrains().size(), 0);
    EXPECT_EQ(turn->getFootprints().size(), 0);
    EXPECT_EQ(turn->getShotguns().size(), 0);
    EXPECT_EQ(turn->getCurrentHand().size(), 0);
}

TEST_F(TurnTest, Turn_Roll)
{
    turn->roll();
    EXPECT_EQ(turn->getCurrentHand().size(), 3);

    int dice_in_total = turn->getBrains().size() + turn->getFootprints().size() + turn->getShotguns().size();
    EXPECT_EQ(dice_in_total, 3);
}

