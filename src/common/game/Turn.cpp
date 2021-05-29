#include "Turn.h"
#include "../exceptions/ZombieException.h"
#include "../serialization/vector_utils.h"

Turn::Turn() : unique_serializable() {
    this->_cup = new Cup();
    this->_current_hand = nullptr;
    this->_brains = nullptr;
    this->_footprints = nullptr;
    this->_shotguns = nullptr;
}

Turn::Turn(
        std::string id,
        std::vector<Die *> *current_hand,
        std::vector<Die *> *brains,
        std::vector<Die *> *footprints,
        std::vector<Die *> *shotguns,
        Cup* cup
           ) :
           unique_serializable(id),
           _current_hand(current_hand),
           _brains(brains),
           _footprints(footprints),
           _shotguns(shotguns),
           _cup(cup)
           {}

int Turn::play_turn() {
    bool done = false;
    while(!done) {
        this->roll();
        std::cin >> done;
        if(_shotguns->size() > 2) {
            done = true;
            return 0;
        }
        // TODO: Update Game State (turn)
    }
    return _brains->size();
}

void Turn::roll() {
    // Is this if here needed?
    if (_shotguns->size() > 2)
        return;

    // Number of dice needed to fill cup
    int draw = 3;
    // Account for footprints rolled in last throw
    draw -= _footprints->size();

    if(!_current_hand) {
        _current_hand = new std::vector<Die*>;
    }
    // TODO:  else clear current_hand

    std::move(_footprints->begin(), _footprints->end(),
              std::back_inserter(*_current_hand));
    _footprints->clear();

    for (int i = 0; i < draw; i++) {
        Die* d = _cup->draw_die();
        _current_hand->push_back(d);
    }
    for (auto d : *_current_hand) {
        Face die_face = d->throw_die();
        switch (die_face) {
            case brain:
                _brains->push_back(d);
                break;
            case footprint:
                _footprints->push_back(d);
                break;
            case shotgun:
                _shotguns->push_back(d);
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

    json.AddMember("current_hand", vector_utils::serialize_vector(*_current_hand, allocator), allocator);

    rapidjson::Value score(rapidjson::kObjectType);
    score.AddMember("brains",vector_utils::serialize_vector(*_brains, allocator), allocator);
    score.AddMember("footprints",vector_utils::serialize_vector(*_footprints, allocator), allocator);
    score.AddMember("shotguns",vector_utils::serialize_vector(*_shotguns, allocator), allocator);

    json.AddMember("score", score, allocator);

}


Turn *Turn::from_json(const rapidjson::Value &json) {
    // TODO: Implement from_json
    return nullptr;
}


