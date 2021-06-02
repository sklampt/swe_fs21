//
// Created by Manuel on 29.01.2021.
//

#include <common/network/responses/server_update_game_event.h>
#include "client_update_game_request.h"
#include "../../../server/game_instance_manager.h"
#include "../../../server/game_instance.h"
#include "../../../gui/GameController.h"


// Public constructor
client_update_game_request::client_update_game_request(Game* state, std::string player_id)
        : client_request(
                client_request::create_base_class_properties(
                        RequestType::client_update_game,
                        uuid_generator::generate_uuid_v4(),
                        player_id)
                        ) {
    this->_state_json = state->to_json();
}

// private constructor for deserialization
client_update_game_request::client_update_game_request(
        client_request::base_class_properties props,
        rapidjson::Value* state_json
        ) : client_request(props),
        _state_json(state_json)
        { }

client_update_game_request* client_update_game_request::from_json(const rapidjson::Value& json) {
    try {
        return new client_update_game_request(
                client_request::extract_base_class_properties(json),
                json_utils::clone_value(json["state_json"].GetObject())
        );
    } catch (std::exception& e) {
        throw ZombieDiceException("Could not parse client_update_game_request from json.");
    }
}

void client_update_game_request::write_into_json(rapidjson::Value &json,
                                         rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    client_request::write_into_json(json, allocator);
    json.AddMember("state_json", *_state_json, allocator);
}

request_response_event* client_update_game_request::execute() {
    std::string err;
    if (this->_state_json != nullptr) {
        // Get new game state from request
        Game* state = Game::from_json(*_state_json);
        // Create dummy player object to exclude requestor from broadcast
        Player* requestor;
        game_instance* game_instance_ptr;
        if (game_instance_manager::try_get_player_and_game_instance(_player_uuid, requestor, game_instance_ptr, err)){
            // NICETOHAVE: Could be improved by changing game parameters instead of just replacing it
            game_instance_ptr->update_game_from_state(*_state_json, requestor);
        }
        return new request_response_event(ResponseType::server_update_game, _request_id, true, state->to_json(), err);
    }
    GameController::showError("Request has not been executed successfully", err);
    // else
    return new request_response_event(ResponseType::request_response, _request_id, false, nullptr, err);
}