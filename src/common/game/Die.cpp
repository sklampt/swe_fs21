//
// Created by marco on 02.05.21.
//

#include "Die.h"


Die::Die(Color c) : _color(c), _dist(std::uniform_int_distribution<int>(1, 6)) {
    std::random_device rd;
    _gen = std::mt19937(rd());
}

void Die::roll() {
    int roll = _dist(_gen);
    switch (_color) {
        case green:
            if (roll < 4) {
                _face = brains;
            } else if (roll < 6) {
                _face = runners;
            } else {
                _face = shotgun;
            }
        case yellow:
            if (roll < 3) {
                _face = brains;
            } else if (roll < 5) {
                _face = runners;
            } else {
                _face = shotgun;
            }
        case red:
            if (roll < 2) {
                _face = brains;
            } else if (roll < 4) {
                _face = runners;
            } else {
                _face = shotgun;
            }
    }

}

Face Die::getFace() {
    return _face;
}
