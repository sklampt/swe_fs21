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
    std::vector<Die> _footsteps;
    std::vector<Die> _shotguns;
    int _num_brains;
    int _num_footprints;
    int _num_shotguns;
    Cup _cup;

public:
    Turn();

    void roll();
    int play_turn();

    int getNumShotguns();

    int getNumFootprints();

    int getNumBrains();
};


#endif //ZOMBIEDICE_TURN_H
