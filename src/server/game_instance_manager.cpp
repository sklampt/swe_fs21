//
// Created by Manuel on 29.01.2021.
//
// The game_instance_manager only exists on the server side. It stores all currently active games and offers
// functionality to retrieve game instances by id and adding players to games.
// If a new player requests to join a game but no valid game_instance is available, then this class
// will generate a new game_instance and add it to the unordered_map of (active) game instances.

#include "game_instance_manager.h"
#include "player_manager.h"
#include "server_network_manager.h"

// Initialize static map
std::unordered_map<std::string, game_instance*> game_instance_manager::games_lut = {};

// Initialize pointer for current server side game_instance
game_instance* game_instance_manager::current_game_instance = nullptr;

void game_instance_manager::create_new_game_instance() {
    current_game_instance = new game_instance();
}

bool game_instance_manager::try_get_game_instance(game_instance*& game_instance_ptr, std::string& err) {
    game_instance_ptr = current_game_instance;
    return true;
}

bool game_instance_manager::try_get_player_and_game_instance(
        Player *& player,
        game_instance*& game_instance_ptr,
        std::string& err
    )
{
    if (player_manager::try_get_player(player->get_id(), player)) {
        if (game_instance_manager::try_get_game_instance(game_instance_ptr, err)) {
            return true;
        } else {
            err = "Could not find game_id" + player->get_game_id() + " associated with this player";
        }
    } else {
        err = "Could not find requested player in database.";
    }
    return false;
}


bool game_instance_manager::try_add_player(Player *player, std::string& err) {
    if (current_game_instance->try_add_player(player, err)) {
        //player->set_game_id(current_game_instance->get_id());   // mark that this player is playing in a src
        return true;
    } else {
        return false;
    }
}

bool game_instance_manager::try_remove_player(Player *player, std::string &err) {
    try {
        return current_game_instance->try_remove_player(player, err);
    }
    catch(std::exception& e) {
        err = "The requested player could not be found.";
        return false;
    }
}


