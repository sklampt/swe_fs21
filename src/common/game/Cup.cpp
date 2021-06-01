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
Cup::Cup(std::string id, std::vector<Die*> dice) : unique_serializable(id), _dice(dice) { }

int Cup::dice_count() {
    return _dice.size();
}

Die* Cup::draw_die() {
    Die* d = _dice[_dice.size()-1];
    _dice.pop_back();
    return d;
}

Cup *Cup::from_json(const rapidjson::Value &json) {
    std::vector<Die*> dice;
    for (auto &die : json["dice"].GetArray()) {
        dice.push_back(Die::from_json(die.GetObject()));
    }

    return new Cup(
            json["id"].GetString(),
            dice
            );
}

void Cup::write_into_json(rapidjson::Value &json,
                          rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    unique_serializable::write_into_json(json, allocator);
    json.AddMember("dice", vector_utils::serialize_vector(_dice, allocator), allocator);
}

