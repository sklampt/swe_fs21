#include "gtest/gtest.h"
#include "common/game/Cup.h"

class CupTest : public ::testing::Test{
protected:
    Cup* cup = new Cup();
};


TEST_F(CupTest, Cup_Constructor_Size)
{
    ASSERT_EQ(cup->dice_count(), 13);
}

TEST_F(CupTest, Cup_Draw_Dice) {
    Die *die = cup->draw_die();
    ASSERT_EQ(cup->dice_count(), 12);
}

TEST_F(CupTest, Cup_Empty_Draw_Dice)
{
    Die* die = cup->draw_die();
    EXPECT_EQ(cup->dice_count(), 12);
    die = cup->draw_die();
    EXPECT_EQ(cup->dice_count(), 11);
    die = cup->draw_die();
    EXPECT_EQ(cup->dice_count(), 10);
    for (int i = 0; i < 9; ++i) {
        die = cup->draw_die();
    }
    EXPECT_EQ(cup->dice_count(), 1);
    die = cup->draw_die();
    EXPECT_EQ(cup->dice_count(), 0);

    EXPECT_EXIT(die = cup->draw_die(), testing::ExitedWithCode(0), "Trying to draw a dice from empty cup. Aborting.\n");
}
