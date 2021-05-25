//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_TURN_H
#define ZOMBIEDICE_TURN_H

#include "Cup.h"
#include "Die.h"
#include <algorithm>
#include <vector>
#include <iostream>

class Turn {
private:
    std::vector<Die> _brains;
    std::vector<Die> _footprint;
    std::vector<Die> _shotguns;
    int _num_brains;
    int _num_footprints;
    int _num_shotguns;
    Cup _cup;

public:
    Turn();

    void roll();
    int play_turn();

    int get_num_shotguns();
    int get_num_footprints();
    int get_num_brains();
};


#endif //ZOMBIEDICE_TURN_H
