//
// Created by david on 5-8-17.
//

#ifndef BASE64_H
#define BASE64_H

#include <string>
#include <array>

class Base64
{
    public:
        static std::string encode(std::string input);
        static std::string decode(std::string input);
    private:
        static int indexof(std::array<char, 64>, char match);
};


#endif //ASE64_H
