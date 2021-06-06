#include "gtest/gtest.h"
#include "common/game/Player.h"

class PlayerTest : public ::testing::Test{
protected:
    Player* player = new Player("Testplayer");
};

TEST_F(PlayerTest, Player_Constructor)
{
    EXPECT_EQ(player->get_score(), 0);
    EXPECT_EQ(player->has_folded(), false);

}

TEST_F(PlayerTest, Player_Update_Score)
{
    player->update_score(5);
    ASSERT_EQ(player->get_score(), 5);
}