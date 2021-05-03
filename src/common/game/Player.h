//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_PLAYER_H
#define ZOMBIEDICE_PLAYER_H


#include <string>
#include "../serialization/uuid_generator.h"
#include "../../../rapidjson/include/rapidjson/document.h"
#include "../serialization/unique_serializable.h"
#include "../serialization/serializable_value.h"


class Player {

private:
    serializable_value<std::string>* _player_name;
    serializable_value<bool>* _has_folded;
    serializable_value<int>* _score;

    std::string _game_id;

    /*
     * Deserialization constructor
     */
    Player(std::string string);

public:
    const std::string get_game_id();

    void set_game_id(std::string basicString);

    void get_id();

    void get_player_name();
};


#endif //ZOMBIEDICE_PLAYER_H
