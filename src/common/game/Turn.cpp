#include "Turn.h"
#include "../exceptions/ZombieException.h"
#include "../serialization/vector_utils.h"

Turn::Turn() : unique_serializable() {
    this->_cup = new Cup();
    this->_current_hand = nullptr;
    this->_num_brains = 0;
    this->_num_footprints = 0;
    this->_num_shotguns = 0;

}

int Turn::play_turn() {
    bool done = false;
    while(!done) {
        this->roll();
        std::cout << "Brains: " << _num_brains << " prints: " << _num_footprints << " shotguns: " << _num_shotguns << std::endl;
        std::cout << "want to end the turn?" << std::endl; // not sure how the game class wants to communicate with this//
        std::cin >> done;
        if(_num_shotguns > 2) {
            done = true;
            return 0;
        }
        // TODO: Update Game State (turn)
    }
    return _num_brains;
}

void Turn::roll() {
    // Is this if here needed?
    if (_num_shotguns > 2)
        return;

    // Number of dice needed to fill cup
    int draw = 3;
    // Account for footprints rolled in last throw
    draw -= _footprints->size();
    _num_footprints -= _footprints->size();


    if(!_current_hand) {
        _current_hand = new std::vector<Die>;
    }
    // TODO:  else clear current_hand

    std::move(_footprints->begin(), _footprints->end(),
              std::back_inserter(*_current_hand));
    _footprints->clear();

    for (int i = 0; i < draw; i++) {
        Die d = _cup.get_die();
        _current_hand->push_back(d);
    }
    for (auto d : *_current_hand) {
        Face die_face = d.throw_die();
        switch (die_face) {
            case brain:
                _brains->push_back(d);
                _num_brains += 1;
                break;
            case footprint:
                _footprints->push_back(d);
                _num_footprints += 1;
                break;
            case shotgun:
                _shotguns->push_back(d);
                _num_shotguns += 1;
                break;
        }
    }
}

int Turn::get_num_shotguns() {
    return _num_shotguns;
}

int Turn::get_num_footprints() {
    return _num_footprints;
}

int Turn::get_num_brains() {
    return _num_brains;
}

void Turn::write_into_json(rapidjson::Value &json,
                           rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const {
    unique_serializable::write_into_json(json, allocator);

    //TODO: We need at least current hand and dice in score vectors.

    //    {
    //        'cup': [ dice ],
    //        'current_hand': [ dice ],
    //        'score': {  'brains': [ dice ],
    //                    'fp': [ dice ],
    //                    'sg': [ dice ]
    //                 }
    //    }

    json.AddMember("cup", vector_utils::serialize_vector(_cup, allocator), allocator);
    json.AddMember("current_hand", vector_utils::serialize_vector(_current_hand, allocator), allocator);

    rapidjson::Value score(rapidjson::kObjectType);
    score.AddMember("brains",vector_utils::serialize_vector(_brains), allocator);
    score.AddMember("footprints",vector_utils::serialize_vector(_footprints), allocator);
    score.AddMember("shotguns",vector_utils::serialize_vector(_shotguns), allocator);
    json.AddMember("score", score, allocator);

}


Turn *Turn::from_json(const rapidjson::Value &json) {
    return nullptr;
}

{'score': {  'brains': val, 'fp': val, 'sg': val } }