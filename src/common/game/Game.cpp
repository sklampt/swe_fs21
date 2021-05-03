//
// Created by marco on 02.05.21.
//

#include "Game.h"

const std::string Game::get_id() {
    return id;
}

bool Game::is_full() {
    return false;
}

bool Game::is_started() {
    return false;
}

bool Game::is_finished() {
    return false;
}

bool Game::start_game(std::string &basicString) {
    return false;
}

const std::vector<Player *> &Game::get_players() {
    return _players;
}

bool Game::remove_player(Player *pPlayer, std::string &basicString) {
    return false;
}

bool Game::add_player(Player *pPlayer, std::string &basicString) {
    return false;
}

rapidjson::Value *Game::to_json() {
    return nullptr;
}

Game *Game::from_json(const rapidjson::Value& json) {
    return nullptr;
}
