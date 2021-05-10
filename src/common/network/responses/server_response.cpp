//
// Created by Manuel on 15.02.2021.
//

#include "server_response.h"
#include "request_response_event.h"
#include "server_update_lobby_event.h"
#include "server_update_game_event.h"

#include "../../exceptions/ZombieException.h"

// for deserialization
const std::unordered_map<std::string, ResponseType> server_response::_string_to_response_type = {
        {"request_response", ResponseType::request_response },
        {"server_update_lobby", ResponseType::server_update_lobby},
        {"server_update_game", ResponseType::server_update_game}
};
// for serialization
const std::unordered_map<ResponseType, std::string> server_response::_response_type_to_string = {
        { ResponseType::request_response,   "request_response" },
        { ResponseType::server_update_lobby, "server_update_lobby"},
        { ResponseType::server_update_game, "server_update_game"}
};

server_response::server_response(server_response::base_class_properties params):_type(params.type) { }

ResponseType server_response::get_type() const {
    return this->_type;
}

server_response::base_class_properties
server_response::create_base_class_properties(ResponseType type) {
    server_response::base_class_properties params;
    params.type = type;
    return params;
}

server_response::base_class_properties server_response::extract_base_class_properties(const rapidjson::Value& json) {
    if (json.HasMember("type")) {
        return create_base_class_properties(server_response::_string_to_response_type.at(json["type"].GetString()));
    } else {
        throw ZombieDiceException("Server Response malformed");
    }
}

server_response *server_response::from_json(const rapidjson::Value& json) {

    if (json.HasMember("type") && json["type"].IsString()) {
        std::string type = json["type"].GetString();
        ResponseType response_type = server_response::_string_to_response_type.at(type);

        if (response_type == ResponseType::request_response) {
            return request_response_event::from_json(json);
        }
        else if (response_type == ResponseType::server_update_game) {
            return server_update_game_event::from_json(json);
        }
        else if (response_type == ResponseType::server_update_lobby) {
            return server_update_lobby_event::from_json(json);
        } else {
            throw ZombieDiceException(&"Encountered unknown ServerResponse type " [ response_type]);
        }
    }
    throw ZombieDiceException("Could not determine type of ClientRequest");
}

void server_response::write_into_json(rapidjson::Value &json,
                                      rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    rapidjson::Value type_val(_response_type_to_string.at(this->_type).c_str(), allocator);
    json.AddMember("type", type_val, allocator);
}



