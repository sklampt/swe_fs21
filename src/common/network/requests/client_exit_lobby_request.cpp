//
// Created by marco on 03.05.21.
//
#include <string>
#include "client_exit_lobby_request.h"
#include "../../../server/game_instance_manager.h"
#include "../../../server/player_manager.h"
#include "../../../server/game_instance.h"

//Public constructor
client_exit_lobby_request::client_exit_lobby_request(std::string player_uuid)
    : client_request(
            client_request::create_base_class_properties(
                    RequestType::client_exit_lobby,
                    uuid_generator::generate_uuid_v4(),
                    player_uuid)
            ),
            _player_uuid(player_uuid) { }

// Private constructor for deserialization
client_exit_lobby_request::client_exit_lobby_request(client_request::base_class_properties props, std::string player_uuid)
        : client_request(props), _player_uuid(player_uuid){ }

void client_exit_lobby_request::write_into_json(
                                rapidjson::Value &json,
                                rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    client_request::write_into_json(json,allocator);
    rapidjson::Value player_uuid_val(_player_uuid.c_str(), allocator);
    json.AddMember("player_uuid", player_uuid_val, allocator);
}

client_exit_lobby_request* client_exit_lobby_request::from_json(const rapidjson::Value &json) {
    if(json.HasMember("player_uuid")) {
        return new client_exit_lobby_request(client_request::extract_base_class_properties(json), json["player_uuid"].GetString());
    } else {
        throw ZombieDiceException("Could not parse client_exit_lobby_request from json. player_uuid is missing.");
    }
}

request_response_event* client_exit_lobby_request::execute() {
    // Player variable is filled by remove_player
    Player* player = nullptr;

    if(player_manager::remove_player(_player_uuid, player)) {
        // Send event with the new player details
        // TODO: Implement get player to json in game instance manager
        // player_json = player_manager::try_get_player_as_json(player);
        std::string err;
        return new request_response_event(ResponseType::server_update_lobby,_request_id,true, nullptr /* player_json */, err);
    } else {
        return new request_response_event(ResponseType::request_response,_request_id, false, nullptr, "Requested game could not be found.");
    }
}
