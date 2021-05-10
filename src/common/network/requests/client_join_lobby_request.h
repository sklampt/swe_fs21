//
// Created by Manuel on 29.01.2021.
//

#ifndef ZOMBIEDICE_JOIN_LOBBY_REQUEST_H
#define ZOMBIEDICE_JOIN_LOBBY_REQUEST_H


#include <string>
#include "client_request.h"
#include "../../../../rapidjson/include/rapidjson/document.h"

class client_join_lobby_request : public client_request{

private:
    std::string _player_uuid;
    std::string _player_name;
    /*
     * Private constructor for deserialization
     */
    client_join_lobby_request(base_class_properties, std::string name);

public:
    /*
     * Constructor to join a server
     */
    client_join_lobby_request(std::string player_uuid, std::string nickname);

    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;
    static client_join_lobby_request* from_json(const rapidjson::Value& json);

    request_response_event* execute() override;
};


#endif //ZOMBIEDICE_JOIN_LOBBY_REQUEST_H
