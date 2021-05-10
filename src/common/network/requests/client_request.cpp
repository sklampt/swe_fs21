// This class receive the message from the server and forwards it to the right processing class e.g. to client_join_lobby_request

#include "client_request.h"
#include "client_join_lobby_request.h"
#include "client_exit_lobby_request.h"
#include "client_update_game_request.h"

#include <iostream>

// for deserialization
const std::unordered_map<std::string, RequestType> client_request::_string_to_request_type = {
        {"client_join_lobby", RequestType::client_join_lobby },
        {"client_exit_lobby", RequestType::client_exit_lobby},
        {"client_update_game", RequestType::client_update_game}
};
// for serialization
const std::unordered_map<RequestType, std::string> client_request::_request_type_to_string = {
        {RequestType::client_join_lobby, "client_join_lobby"},
        {RequestType::client_exit_lobby, "client_exit_lobby"},
        {RequestType::client_update_game, "client_update_game"}
};

// protected constructor. only used by subclasses
client_request::client_request(client_request::base_class_properties props) :
        _request_type(props._request_type),
        _request_id(props._request_id),
        _player_uuid(props._player_uuid)
{ }


// used by subclasses to retrieve information from the json stored by this superclass
client_request::base_class_properties client_request::extract_base_class_properties(const rapidjson::Value& json) {

    if (json.HasMember("player_uuid") && json.HasMember("request_id")) {
        std::string player_uuid = json["player_uuid"].GetString();
        std::string request_id = json["request_id"].GetString();

        return create_base_class_properties(
                client_request::_string_to_request_type.at(json["request_type"].GetString()),
                request_id,
                player_uuid
        );
    }
    else
    {
        throw ZombieDiceException("Client Request did not contain player_id or game_id");
    }
}

client_request::base_class_properties client_request::create_base_class_properties(
        RequestType request_type,
        std::string request_id,
        std::string& player_uuid
        )
{
    client_request::base_class_properties res;
    res._player_uuid = player_uuid;
    res._request_id = request_id;
    res._request_type = request_type;
    return res;
}


std::string client_request::get_player_uuid() const {
    return this->_player_uuid;
}

void client_request::write_into_json(rapidjson::Value &json,
                                     rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    rapidjson::Value type_val(_request_type_to_string.at(this->_request_type).c_str(), allocator);
    json.AddMember("request_type", type_val, allocator);

    rapidjson::Value player_id_val(_player_uuid.c_str(), allocator);
    json.AddMember("player_uuid", player_id_val, allocator);

    rapidjson::Value request_id_val(_request_id.c_str(), allocator);
    json.AddMember("request_id", request_id_val, allocator);
}

client_request* client_request::from_json(const rapidjson::Value &json) {
    if (json.HasMember("request_type") && json["request_type"].IsString()) {
        const std::string request_type_val = json["request_type"].GetString();
        const RequestType request_type = client_request::_string_to_request_type.at(request_type_val);

        // Check which type of request it is and call the respective from_json constructor
        if (request_type == RequestType::client_join_lobby) {
            return client_join_lobby_request::from_json(json);
        }
        else if (request_type == RequestType::client_exit_lobby) {
            return client_exit_lobby_request::from_json(json);
        }
        else if (request_type == RequestType::client_update_game) {
            return client_update_game_request::from_json(json);
        } else {
            throw ZombieDiceException(&"Encountered unknown ClientRequest type " [request_type]);
        }
    }
    throw ZombieDiceException("Could not determine type of ClientRequest. JSON was:\n" + json_utils::to_string(&json));
}


std::string client_request::to_string() const {
    return "client_request of type " + client_request::_request_type_to_string.at(_request_type) + " for playerId " + _player_uuid;
}





