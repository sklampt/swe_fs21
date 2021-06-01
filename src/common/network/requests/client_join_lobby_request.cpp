//
// Created by Manuel on 29.01.2021.
//
#include <string>
#include "client_join_lobby_request.h"
#include "../../../server/game_instance_manager.h"
#include "../../../server/player_manager.h"
#include "../../../server/game_instance.h"

// Public constructor
client_join_lobby_request::client_join_lobby_request(std::string player_uuid, std::string nickname)
        : client_request(
                client_request::create_base_class_properties(
                        RequestType::client_join_lobby,
                        uuid_generator::generate_uuid_v4(),
                        player_uuid)
                        ),
                _player_name(nickname), _player_uuid(player_uuid) { }

// private constructor for deserialization
client_join_lobby_request::client_join_lobby_request(
        client_request::base_class_properties props,
        std::string player_name,
        std::string player_uuid
        ) : client_request(props),
        _player_name(player_name),
        _player_uuid(player_uuid)
        { }

void client_join_lobby_request::write_into_json(rapidjson::Value &json,
                                        rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    client_request::write_into_json(json, allocator);
    rapidjson::Value name_val(_player_name.c_str(), allocator);
    json.AddMember("player_name", name_val, allocator);
}

client_join_lobby_request* client_join_lobby_request::from_json(const rapidjson::Value& json) {
    if (json.HasMember("player_name") && json.HasMember("player_uuid")) {
        return new client_join_lobby_request(client_request::extract_base_class_properties(json), json["player_name"].GetString(), json["player_uuid"].GetString());
    } else {
        throw ZombieDiceException("Could not parse client_join_lobby_request from json. player_name is missing.");
    }
}


request_response_event* client_join_lobby_request::execute() {
    Player* player;
    player_manager::add_or_get_player(_player_name, _player_uuid, player);

    std::string err;
    game_instance* game_instance_ptr;
    if (game_instance_manager::try_add_player(player, err)) {
        if(game_instance_manager::try_get_game_instance(game_instance_ptr, err))
            return new request_response_event(
                    ResponseType::request_response,
                    _request_id,
                    true,
                    game_instance_ptr->get_game()->to_json(),
                    err
                    );
    } else {
        return new request_response_event(ResponseType::request_response,
                                          _request_id,
                                          false,
                                          nullptr,
                                          "Request couldn't be executed: " + err
                                          );
    }

}
