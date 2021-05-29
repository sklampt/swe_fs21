#include <common/serialization/vector_utils.h>
#include "Cup.h"

Cup::Cup() {
    std::random_device rd;
    std::mt19937 g(rd());
    for (int i = 0; i < 6; i++)
        _dice.emplace_back(new Die(green));
    for (int i = 0; i < 4; i++)
        _dice.emplace_back(new Die(yellow));
    for (int i = 0; i < 3; i++)
        _dice.emplace_back(new Die(red));
    std::shuffle(_dice.begin(), _dice.end(), g);
}

// Serialization constructur
Cup::Cup(std::vector<Die*> dice) : _dice(dice) { }

int Cup::dice_count() {
    return _dice.size();
}

Die* Cup::draw_die() {
    Die* d = _dice[_dice.size()];
    _dice.pop_back();
    return d;
}

Cup *Cup::from_json(const rapidjson::Value &json) {
    // TODO: Write from_json
    return nullptr;
}

void Cup::write_into_json(rapidjson::Value &json,
                          rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    unique_serializable::write_into_json(json, allocator);
    json.AddMember("dice", vector_utils::serialize_vector(_dice, allocator), allocator);
}

