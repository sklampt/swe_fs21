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



game_instance* game_instance_manager::create_new_game() {
    game_instance* game = new game_instance();
    //TODO: Save game pointer to be called again.
    return game;
}

bool game_instance_manager::try_get_game_instance(game_instance* game_instance_ptr, std::string& err) {
    //TODO: assign game to pointer
    return false;
}

bool game_instance_manager::try_get_player_and_game_instance(
        Player *&player,
        game_instance *&game_instance_ptr,
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
    //TODO: Implement add_player
    return false;
}

bool game_instance_manager::try_remove_player(Player *player, std::string &err) {
    try {
        return try_remove_player(player, err);
    }
    catch(std::exception& e) {
        err = "The requested player could not be found.";
        return false;
    }
}


