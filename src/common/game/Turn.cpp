//
// Created by marco on 02.05.21.
//

#include "Turn.h"

Turn::Turn() : _cup(Cup()), _num_brains(0), _num_footprints(0), _num_shotguns(0) {}

void Turn::roll() {
    if (_num_shotguns > 2)
        return;
    int draw = 3;
    draw -= _footsteps.size();
    _num_footprints -= _footsteps.size();
    std::vector<Die> current_hand;
    std::move(_footsteps.begin(), _footsteps.end(),
              std::back_inserter(current_hand));
    _footsteps.clear();
    for (int i = 0; i < draw; i++) {
        Die d = _cup.get_die();
        current_hand.push_back(d);
    }
    for (auto d : current_hand) {
        Face die_face = d.throw_die();
        switch (die_face) {
            case brain:
                _brains.push_back(d);
                _num_brains += 1;
                break;
            case footprint:
                _footprint.push_back(d);
                _num_footprints += 1;
                break;
            case shotgun:
                _shotguns.push_back(d);
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

int Turn::play_turn() {
    bool done = false;
    while(!done) {
        roll();
        std::cout << "Brains: " << _num_brains << " prints: " << _num_footprints << " shotguns: " << _num_shotguns << std::endl;
        std::cout << "want to end the turn?" << std::endl; // not sure how the game class wants to communicate with this//
        std::cin >> done;
        if(_num_shotguns > 2) {
            done = true;
            return 0;
        }
    }
    return _num_brains;
}
