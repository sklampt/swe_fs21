#ifndef ZOMBIEDICE_TURN_H
#define ZOMBIEDICE_TURN_H

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

#include "Cup.h"
#include "Die.h"
#include "../../../rapidjson/include/rapidjson/document.h"
#include "../serialization/serializable.h"
#include "../serialization/serializable_value.h"
#include "../serialization/unique_serializable.h"



class Turn : public unique_serializable {

private:
    Cup* _cup;

    std::vector<Die*> *_brains;
    std::vector<Die*> *_footprints;
    std::vector<Die*> *_shotguns;
    std::vector<Die*> *_current_hand;

    // Serialization constructor
    Turn(
            std::string id,
            std::vector<Die *> *current_hand,
            std::vector<Die *> *brains,
            std::vector<Die *> *footprints,
            std::vector<Die *> *shotguns,
            Cup* cup // Cup could be reconstructed from other values
            );

public:
    Turn();

    void roll();
    int play_turn();

    static Turn *from_json(const rapidjson::Value& json);

    virtual void write_into_json(rapidjson::Value& json,
                         rapidjson::Document::AllocatorType& allocator
                         ) const override;
};


#endif //ZOMBIEDICE_TURN_H
