//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_CUP_H
#define ZOMBIEDICE_CUP_H

#include <vector>
#include <random>
#include <algorithm>

#include "Die.h"
#include <common/serialization/unique_serializable.h>

class Cup: public unique_serializable {
private:
    std::vector<Die*> _dice;

    // Serialization constructor
    Cup(std::string id, std::vector<Die*> dice);

public:
    Cup();
    // ~Cup(); not needed but we could implement it anyway
    int dice_count();
    Die * draw_die();

    static Cup *from_json(const rapidjson::Value& json);
    virtual void write_into_json(rapidjson::Value& json,
                                 rapidjson::Document::AllocatorType& allocator
                                 ) const override;
};


#endif //ZOMBIEDICE_CUP_H
