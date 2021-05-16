//
// Created by Manuel on 29.01.2021.
//

#include "client_update_game_request.h"

// #ifdef LAMA_SERVER
#include "../../../server/game_instance_manager.h"
#include "../../../server/game_instance.h"
// #endif

// Public constructor
client_update_game_request::client_update_game_request(std::string game_id, std::string player_id)
        : client_request( client_request::create_base_class_properties(RequestType::client_update_game, uuid_generator::generate_uuid_v4(), player_id) )
{ }

// private constructor for deserialization
client_update_game_request::client_update_game_request(client_request::base_class_properties props) :
        client_request(props)
{ }

client_update_game_request* client_update_game_request::from_json(const rapidjson::Value& json) {
    return new client_update_game_request(client_request::extract_base_class_properties(json));
}

void client_update_game_request::write_into_json(rapidjson::Value &json,
                                         rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    client_request::write_into_json(json, allocator);
}

request_response_event* client_update_game_request::execute() {
    std::string err;
    Player* player;
    game_instance* game_instance_ptr;
    if (game_instance_manager::try_get_player_and_game_instance(player, game_instance_ptr, err)) {
        if (game_instance_ptr->start_game(player, err)) {
            return new request_response_event(ResponseType::server_update_game, _request_id, true, game_instance_ptr->get_game()->to_json(), err);
        }
    }
    // else
    return new request_response_event(ResponseType::server_update_game, _request_id, false, nullptr, err);
}