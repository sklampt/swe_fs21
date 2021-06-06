#include "gtest/gtest.h"
#include "common/game/Game.h"
#include "common/game/Player.h"
#include <string>

class GameTest : public ::testing::Test{
protected:
    Game* game = new Game();
};

TEST_F(GameTest, Game_Constructor)
{
    EXPECT_FALSE(game->is_full());
    EXPECT_FALSE(game->is_started());
    EXPECT_FALSE(game->is_finished());

    EXPECT_EQ(game->get_round_number(), 0);
}

TEST_F(GameTest, Game_Add_Player_When_Full)
{
    int id = 0;
    std::string error_msg = "";
    while(!game->is_full()){
        Player* player = new Player(std::to_string(id++), "Player");
        game->add_player(player, error_msg);
    }

    EXPECT_TRUE(game->is_full());
    int max_players = game->get_players().size();

    Player* player = new Player(std::to_string(id++), "Player_When_Full");
    game->add_player(player, error_msg);

    EXPECT_EQ(game->get_players().size(), max_players);
}

TEST_F(GameTest, Game_Player_In_Game)
{
    int id = 0;
    std::string error_msg = "";
    Player* player;
    while(!game->is_full()){
        player = new Player(std::to_string(id++), "Player");
        game->add_player(player, error_msg);
    }

    EXPECT_TRUE(game->is_player_in_game(player));
}

TEST_F(GameTest, Game_Player_Not_In_Game)
{
    int id = 0;
    std::string error_msg = "";
    Player* player1 = new Player(std::to_string(id++), "Player1");
    game->add_player(player1, error_msg);

    Player* player2 = new Player(std::to_string(id++), "Player2");

    EXPECT_FALSE(game->is_player_in_game(player2));
}