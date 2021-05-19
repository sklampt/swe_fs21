//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_DIE_H
#define ZOMBIEDICE_DIE_H

#include <random>

enum Color {
    green, yellow, red
};
enum Face {
    brains, runners, shotgun
};

class Die {
private:
    Color _color;
    Face _face;
    std::mt19937 _gen;
    std::uniform_int_distribution _dist;
public:
    Die(Color c);

    Face getFace();

    void roll();
};


#endif //ZOMBIEDICE_DIE_H
