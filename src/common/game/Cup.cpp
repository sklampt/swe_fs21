//
// Created by marco on 02.05.21.
//

#include "Cup.h"

Cup::Cup() : _num_dice(13) {
    std::random_device rd;
    std::mt19937 g(rd());
    for (int i = 0; i < 6; i++)
        _dice.emplace_back(green);
    for (int i = 0; i < 4; i++)
        _dice.emplace_back(yellow);
    for (int i = 0; i < 3; i++)
        _dice.emplace_back(red);
    std::shuffle(_dice.begin(), _dice.end(), g);
}

int Cup::dice_count() {
    return _dice.size();
}

Die Cup::get_die() {
    Die d = _dice[_dice.size()];
    _dice.pop_back();
    _num_dice -= 1;
    return d;
}
