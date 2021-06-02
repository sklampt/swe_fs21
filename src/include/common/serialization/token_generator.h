//
// Created by marco on 03.05.21.
//

#ifndef ZOMBIEDICE_TOKEN_GENERATOR_H
#define ZOMBIEDICE_TOKEN_GENERATOR_H

#include <random>
#include <sstream>

class token_generator {
private:

public:
    constexpr const static char letters[26] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    static std::string generate() {
        std::stringstream ss;
        for (int i = 0; i < 8; ++i) {
            if (i == 4) {ss << "-";}
            ss << letters[rand() % 26];
        }
        return ss.str();
    }
};


#endif //ZOMBIEDICE_TOKEN_GENERATOR_H
