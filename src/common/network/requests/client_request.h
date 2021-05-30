//
// Created by Manuel on 28.01.2021.
//
// client_request is the base-class for all requests that are being sent from the client to the server.
// It offers a function to deserialize a client_request subclass from a valid json.

#ifndef ZOMBIEDICE_CLIENT_REQUEST_H
#define ZOMBIEDICE_CLIENT_REQUEST_H

#include <string>
#include <unordered_map>
#include "../../../../rapidjson/include/rapidjson/document.h"
#include "../../serialization/serializable.h"
#include "../../exceptions/ZombieException.h"
#include "../../serialization/uuid_generator.h"
#include "../../serialization/json_utils.h"
#include "../responses/server_response.h"
#include "../responses/request_response_event.h"


// Identifier for the different request types.
// The RequestType is sent with every client_request to identify the type of client_request
// during deserialization on the server side.
enum RequestType {
    client_join_lobby,
    client_exit_lobby,
    client_update_game
};

class client_request : public serializable {

protected:
    struct base_class_properties {
        RequestType _request_type;
        std::string _request_id;
        std::string _player_uuid;
    };

    RequestType _request_type;
    std::string _request_id;
    std::string _player_uuid;

    explicit client_request(base_class_properties); // base constructor

    static base_class_properties create_base_class_properties(
            RequestType type, std::string request_id,std::string& player_uuid
            );

    static base_class_properties extract_base_class_properties(const rapidjson::Value& json);

private:
    // for deserialization
    static const std::unordered_map<std::string, RequestType> _string_to_request_type;
    // for serialization
    static const std::unordered_map<RequestType, std::string> _request_type_to_string;

public:
    virtual ~client_request() {}

    std::string get_player_uuid() const;

    // Tries to create the specific client_request from the provided json.
    // Throws exception if parsing fails -> Use only in "try{ }catch()" block
    static client_request* from_json(const rapidjson::Value& json);

    // Serializes the client_request into a json object that can be sent over the network
    void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;

    virtual std::string to_string() const;

    // Execute this request on the server side
    virtual request_response_event* execute() = 0;
};


#endif //ZOMBIEDICE_CLIENT_REQUEST_H
