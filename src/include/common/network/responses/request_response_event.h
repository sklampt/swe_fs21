//
// Created by Manuel on 15.02.2021.
//

#ifndef LAMA_REQUEST_RESPONSE_H
#define LAMA_REQUEST_RESPONSE_H

#include <string>
#include "server_response.h"


class request_response_event : public server_response {
private:
    bool _success;
    std::string _err;
    std::string _req_id;
    rapidjson::Value* _state_json = nullptr;

    request_response_event(base_class_properties props, std::string req_id, bool success, rapidjson::Value* state_json, std::string& err);

public:

    request_response_event(ResponseType response_type, std::string req_id, bool success, rapidjson::Value* state_json, std::string err);

    ~request_response_event();

    virtual void write_into_json(rapidjson::Value& json, rapidjson::Document::AllocatorType& allocator) const override;

    static request_response_event* from_json(const rapidjson::Value& json);

    virtual void Process() const override;
};


#endif //LAMA_REQUEST_RESPONSE_H
