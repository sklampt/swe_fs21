//
// Created by marco on 02.05.21.
//

#include "Player.h"

void Player::set_game_id(std::string basicString) {

}

const std::string Player::get_game_id() {
    return reinterpret_cast<const char *>(_game_id);
}

std::string Player::get_id() {
    return reinterpret_cast<const std::basic_string<char> &>(_player_uuid);
}

void Player::get_player_name() {

}
