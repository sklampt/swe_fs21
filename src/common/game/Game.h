//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_GAME_H
#define ZOMBIEDICE_GAME_H


#include <string>
#include "Player.h"

class Game {

private:
    std::vector<Player*> _players;
    std::string id;

public:
    const std::string get_id();

    bool is_allowed_to_play_now(Player *pPlayer);

    bool is_full();

    bool is_started();

    bool is_finished();

    bool start_game(std::string &basicString);

    const std::vector<Player *> &get_players();

    bool remove_player(Player *pPlayer, std::string &basicString);

    bool add_player(Player *pPlayer, std::string &basicString);

    rapidjson::Value *to_json();

    static Game *from_json(const rapidjson::Value& json);
};


#endif //ZOMBIEDICE_GAME_H
