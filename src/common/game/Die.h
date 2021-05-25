//
// Created by marco on 02.05.21.
//

#ifndef ZOMBIEDICE_DIE_H
#define ZOMBIEDICE_DIE_H

#include <vector>

// three colors of dice
enum Color {green, yellow, red};
// three faces present on dice
enum Face {brain, shotgun, footprint};

class Die {
    private:
        std::vector<Face> faces;
        Color color;
    
    public:
        Die(Color color);
        Color get_color();
        Face throw_die();
};


#endif //ZOMBIEDICE_DIE_H
