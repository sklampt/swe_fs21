//
// Created by marco on 03.05.21.
//

#ifndef ZOMBIEDICE_CLIENT_EXIT_LOBBY_REQUEST_H
#define ZOMBIEDICE_CLIENT_EXIT_LOBBY_REQUEST_H


#include "client_request.h"

class client_exit_lobby_request : public client_request {

private:
    std::string _player_uuid;
    /*
    * Private constructor for deserialization
    */
    client_exit_lobby_request(base_class_properties, std::string player_uuid);


public:
    /*
     * Constructor to exit a server
     */
    client_exit_lobby_request(std::string player_uuid);

    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;
    static client_exit_lobby_request* from_json(const rapidjson::Value& json);

    request_response_event* execute() override;

};


#endif //ZOMBIEDICE_CLIENT_EXIT_LOBBY_REQUEST_H
