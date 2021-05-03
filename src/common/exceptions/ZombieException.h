//
// Created by Manuel on 09.03.2021.
//

#ifndef ZOMBIEDICE_ZOMBIEDICEEXCEPTION_H
#define ZOMBIEDICE_ZOMBIEDICEEXCEPTION_H

#include <string>

class ZombieDiceException : public std::exception {
private:
    std::string _msg;
public:
    explicit ZombieDiceException(const std::string& message) : _msg(message) { };

    const char* what() const noexcept override {
        return _msg.c_str();
    }
};

#endif //ZOMBIEDICE_ZOMBIEDICEEXCEPTION_H
