#include "server_update_game_event.h"
#include "../../exceptions/ZombieException.h"
#include "../../serialization/json_utils.h"
#include "../../../gui/GameController.h"

server_update_game_event::server_update_game_event(server_response::base_class_properties props, rapidjson::Value* state_json) :
        server_response(props),
        _state_json(state_json)
{ }

server_update_game_event::server_update_game_event(Game state) :
        server_response(server_response::create_base_class_properties(ResponseType::server_update_lobby))
{
    this->_state_json = state.to_json();
}

void server_update_game_event::write_into_json(rapidjson::Value &json,
                                          rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    server_response::write_into_json(json, allocator);
    json.AddMember("state_json", *_state_json, allocator);
}

server_update_game_event *server_update_game_event::from_json(
        const rapidjson::Value& json)
{
    if (json.HasMember("state_json")) {
        return new server_update_game_event(
                server_response::extract_base_class_properties(json),
                json_utils::clone_value(json["state_json"].GetObject())
                );
    } else {
        throw ZombieDiceException(
                "Could not parse server_update_game_event from json. state is missing."
                );
    }
}

server_update_game_event::~server_update_game_event() {
    if (_state_json != nullptr) {
        delete _state_json;
        _state_json = nullptr;
    }
}

rapidjson::Value* server_update_game_event::get_state_json() const {
    return _state_json;
}

//#ifdef LAMA_CLIENT

void server_update_game_event::Process() const {
    try {
        Game* state = Game::from_json(*_state_json);
        //GameController::updateGameState(state);

    } catch(std::exception& e) {
        std::cerr << "Failed to extract game_state from server_update_game_event" << std::endl
                  << e.what() << std::endl;
    }
}

// #endif
