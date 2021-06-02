//
// Created by Manuel on 25.01.2021.
//
// The game_instance class is a wrapper around the Game of an active instance of the game.
// This class contains functions to modify the contained Game.

#include <common/network/responses/server_update_lobby_event.h>
#include "game_instance.h"

#include "server_network_manager.h"
#include "../common/network/responses/server_update_game_event.h"


game_instance::game_instance() {
    _Game = new Game();
}

Game *game_instance::get_game() {
    return _Game;
}

void game_instance::update_game_from_state(const rapidjson::Value &json, Player *player) {
    modification_lock.lock();
    _Game = Game::from_json(json);
    // send state update to all other players
    server_update_game_event state_update_msg = server_update_game_event( *_Game);
    server_network_manager::broadcast_message(state_update_msg, _Game->get_players(), player);
    modification_lock.unlock();
}

std::string game_instance::get_id() {
    return _Game->get_id();
}

bool game_instance::is_full() {
    return _Game->is_full();
}

bool game_instance::is_started() {
    return _Game->is_started();
}

bool game_instance::is_finished() {
    return _Game->is_finished();
}

bool game_instance::start_game(Player* player, std::string &err) {
    modification_lock.lock();
    if (_Game->start_game(err)) {
        // send state update to all other players
        server_update_game_event state_update_msg = server_update_game_event( *_Game);
        server_network_manager::broadcast_message(state_update_msg, _Game->get_players(), player);
        modification_lock.unlock();
        return true;
    }
    modification_lock.unlock();
    return false;
}

bool game_instance::try_remove_player(Player *player, std::string &err) {
    modification_lock.lock();
    if (_Game->remove_player(player, err)) {
        player->set_game_id("");
        // send state update to all other players
        server_update_lobby_event state_update_msg = server_update_lobby_event(_Game);
        server_network_manager::broadcast_message(state_update_msg, _Game->get_players(), player);
        modification_lock.unlock();
        return true;
    }
    modification_lock.unlock();
    return false;
}

bool game_instance::try_add_player(Player *new_player, std::string &err) {
    modification_lock.lock();
    if (_Game->add_player(new_player, err)) {
        new_player->set_game_id(get_id());
        // send state update to all other players
        server_update_lobby_event state_update_msg = server_update_lobby_event(_Game);
        server_network_manager::broadcast_message(state_update_msg, _Game->get_players(), new_player);
        modification_lock.unlock();
        return true;
    }
    modification_lock.unlock();
    return false;
}


