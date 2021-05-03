//
// Created by Manuel on 25.01.2021.
//
// The game_instance class is a wrapper around the game_state of an active instance of the game.
// This class contains functions to modify the contained game_state.

#ifndef LAMA_GAME_H
#define LAMA_GAME_H

#include <vector>
#include <string>
#include <mutex>

#include "../common/game/Player.h"
#include "../common/game/Game.h"

class game_instance {

private:
    Game* _Game;
    bool is_player_allowed_to_play(Player* player);
    inline static std::mutex modification_lock;

public:
    game_instance();
    ~game_instance() {
        if (_Game != nullptr) {
            delete _Game;
        }
        _Game = nullptr;
    }
    std::string get_id();

    Game* get_game();

    bool is_full();
    bool is_started();
    bool is_finished();

    // game update functions
    bool start_game(Player* player, std::string& err);
    bool try_add_player(Player* new_player, std::string& err);
    bool try_remove_player(Player* player, std::string& err);
    bool play_card(Player* player, const std::string& card_id, std::string& err);
    // bool draw_card(Player* player, card*& drawn_card, std::string& err);
    bool fold(Player* player, std::string& err);

};


#endif //LAMA_GAME_H

