//
// Created by Manuel on 29.01.2021.
//

#ifndef LAMA_START_GAME_REQUEST_H
#define LAMA_START_GAME_REQUEST_H


#include <string>
#include <common/game/Game.h>
#include "client_request.h"
#include "../../../../rapidjson/include/rapidjson/document.h"


class client_update_game_request : public client_request{

private:
    rapidjson::Value* _state_json;

    /*
     * Private constructor for deserialization
     */
    client_update_game_request(base_class_properties, rapidjson::Value* state_json);

public:
    client_update_game_request(Game* state , std::string player_id);
    // TODO: Deconstructor?

    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;
    static client_update_game_request* from_json(const rapidjson::Value& json);

    request_response_event* execute() override;
};

#endif //LAMA_START_GAME_REQUEST_H
