//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_CUP_H
#define ZOMBIEDICE_CUP_H

#include "Die.h"
#include <vector>
#include <random>
#include <algorithm>

class Cup {
private:
    std::vector<Die> _dice;
    int _num_dice;
public:
    Cup();

    int dice_count();

    Die get_die();
};


#endif //ZOMBIEDICE_CUP_H
