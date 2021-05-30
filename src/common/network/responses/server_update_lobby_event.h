//
// Created by marco on 03.05.21.
//

#ifndef ZOMBIEDICE_SERVER_UPDATE_LOBBY_EVENT_H
#define ZOMBIEDICE_SERVER_UPDATE_LOBBY_EVENT_H

#include "server_response.h"
#include "server/player_manager.h"
#include "../../game/Game.h"

class server_update_lobby_event: public server_response {
private:
    rapidjson::Value* _state_json;

    /*
     * Private constructor for deserialization
     */
    server_update_lobby_event(base_class_properties props, rapidjson::Value* state_json);

public:
    server_update_lobby_event(Game* state);
    ~server_update_lobby_event();

    rapidjson::Value* get_state_json() const;

    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;
    static server_update_lobby_event* from_json(const rapidjson::Value& json);

    virtual void Process() const override;
};

#endif //ZOMBIEDICE_SERVER_UPDATE_LOBBY_EVENT_H
