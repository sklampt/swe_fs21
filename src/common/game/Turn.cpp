#include "Turn.h"
#include "../exceptions/ZombieException.h"
#include "../serialization/vector_utils.h"

Turn::Turn() : unique_serializable() {
    this->_cup = new Cup();
    this->_current_hand = std::vector<Die *>();
    this->_brains = std::vector<Die *>();
    this->_footprints = std::vector<Die *>();
    this->_shotguns = std::vector<Die *>();
}

Turn::Turn(
        std::string id,
        std::vector<Die *> current_hand,
        std::vector<Die *> brains,
        std::vector<Die *> footprints,
        std::vector<Die *> shotguns,
        Cup* cup
           ) :
           unique_serializable(id),
           _current_hand(current_hand),
           _brains(brains),
           _footprints(footprints),
           _shotguns(shotguns),
           _cup(cup)
           {}


bool Turn::play_turn() {
    this->roll();
    if(_shotguns.size() > 2) {
        return true;
    }
    return false;
}

int Turn::end_turn() {

    return _brains.size();
}

void Turn::roll() {
    // Is this if here needed?
    if (_shotguns.size() > 2)
        return;

    // Number of dice needed to fill cup
    int draw = 3;
    // Account for footprints rolled in last throw
    draw -= _footprints.size();

    // Clear current hand
   _current_hand.clear();

    std::move(_footprints.begin(), _footprints.end(),
              std::back_inserter(_current_hand));
    _footprints.clear();

    for (int i = 0; i < draw; i++) {
        Die* d = _cup->draw_die();
        _current_hand.push_back(d);
    }
    for (auto d : _current_hand) {
        Face die_face = d->throw_die();
        switch (die_face) {
            case brain:
                _brains.push_back(d);
                break;
            case footprint:
                _footprints.push_back(d);
                break;
            case shotgun:
                _shotguns.push_back(d);
                break;
            case undefined:
                throw ZombieDiceException("Error in throw_die()");
        }
    }
}

void Turn::write_into_json(rapidjson::Value &json,
                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    unique_serializable::write_into_json(json, allocator);

    //    {
    //        'cup': [ dice ],
    //        'current_hand': [ dice ],
    //        'score': {  'brains': [ dice ],
    //                    'footprints': [ dice ],
    //                    'shotguns': [ dice ]
    //                 }
    //    }

    rapidjson::Value cup_val(rapidjson::kObjectType);
    _cup->write_into_json(cup_val, allocator);
    json.AddMember("cup", cup_val, allocator);

    json.AddMember("current_hand", vector_utils::serialize_vector(_current_hand, allocator), allocator);

    rapidjson::Value score(rapidjson::kObjectType);
    score.AddMember("brains",vector_utils::serialize_vector(_brains, allocator), allocator);
    score.AddMember("footprints",vector_utils::serialize_vector(_footprints, allocator), allocator);
    score.AddMember("shotguns",vector_utils::serialize_vector(_shotguns, allocator), allocator);

    json.AddMember("score", score, allocator);

}

Turn* Turn::from_json(const rapidjson::Value &json) {

    std::vector<Die *> current_hand;
    for (auto &die : json["current_hand"].GetArray()) {
        current_hand.push_back(Die::from_json(die.GetObject()));
    }
    std::vector<Die *> brains;
    for (auto &die : json["score"]["brains"].GetArray()) {
        brains.push_back(Die::from_json(die.GetObject()));
    }
    std::vector<Die *> footprints;
    for (auto &die : json["score"]["footprints"].GetArray()) {
        footprints.push_back(Die::from_json(die.GetObject()));
    }
    std::vector<Die *> shotguns;
    for (auto &die : json["score"]["shotguns"].GetArray()) {
        shotguns.push_back(Die::from_json(die.GetObject()));
    }

    Cup* cup = Cup::from_json(json["cup"]);

    return new Turn(
            json["id"].GetString(),
            current_hand,
            brains,
            footprints,
            shotguns,
            cup
            );
}

Cup *Turn::getCup() const {
    return _cup;
}

std::vector<Die *> Turn::getBrains() const {
    return _brains;
}

std::vector<Die *> Turn::getFootprints() const {
    return _footprints;
}

std::vector<Die *> Turn::getShotguns() const {
    return _shotguns;
}

std::vector<Die *> Turn::getCurrentHand() const {
    return _current_hand;
}


