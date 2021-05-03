//
// Created by Manuel on 15.02.2021.
//

#ifndef ZOMBIEDICE_FULL_STATE_RESPONSE_H
#define ZOMBIEDICE_FULL_STATE_RESPONSE_H

#include "server_response.h"
#include "../../game/Game.h"

class full_state_response : public server_response {
private:
    rapidjson::Value* _state_json;

    /*
     * Private constructor for deserialization
     */
    full_state_response(base_class_properties props, rapidjson::Value* state_json);

public:

    full_state_response(std::string game_id, Game state);
    ~full_state_response();

    rapidjson::Value* get_state_json() const;

    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;
    static full_state_response* from_json(const rapidjson::Value& json);

// #ifdef ZOMBIEDICE_CLIENT
    virtual void Process() const override;
// #endif
};


#endif //ZOMBIEDICE_FULL_STATE_RESPONSE_H
