//
// Created by david on 5-8-17.
//

#include "Base64.h"

#include <cstdlib>
#include <iostream>
#include <bitset>
#include <vector>


std::string Base64::encode(std::string input)
{
    // Base64 conversion table
    std::array<char, 64> table = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                  'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

    std::string binary;
    // Converts input to binary
    for (unsigned i = 0; i < input.size(); i++)
    {

        std::bitset<8> b(input[i]);
        binary += b.to_string();
    }
    // how much 0's should be added
    int rest = binary.length() % 6;

    if(rest != 0)
    {
        rest = 6 - rest;
    }

    // Add '0's
    for(unsigned i = 0; i < rest; i++)
    {
        binary += "0";
    }

    std::string result;
    std::string buffer;

    int loopcount = 0;


    while(true)
    {

        // Add 6 bits to buffer
        for(int i =0; i < 6; i++)
        {
            buffer += binary[i + (loopcount * 6)];
        }

        // Add result of table[number that the 6 bits represent + 1]

        result += table[std::bitset<6>(buffer).to_ulong()];

        // Clear buffer
        buffer = "";

        loopcount++;

        // Break when all groups of 6 bits are added to result
        if(binary.length() / 6 == loopcount)
        {
            break;
        }
    }
    // Add '='s if necessary
    for(int i = 0; i < rest; i += 2)
    {
        result += "=";
    }

    return result;
}

std::string Base64::decode(std::string input)
{
    std::array<char, 64> table = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                  'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
    size_t loc;
    int equal_sign_count = 0;

    // Strip equal to signs.
    while(true)
    {

        loc = input.find_first_of('=');

        // If not found
        if(loc > input.length())
        {

            break;
        }

        input.erase(loc, 1);

        equal_sign_count++;
    }

    std::string bin;
    for(int i = 0; i < input.size(); i++)
    {
        std::bitset<6> b(indexof(table, input[i]));

        bin += b.to_string();
    }


    // Clean up padding if necessary
    if(equal_sign_count > 0)
    {
        bin.erase(bin.size() - equal_sign_count * 2);
    }

    std::string buffer, result;
    int loopcount = 0;

    while(true)
    {

        // Add 8 bits to buffer
        for(int i =0; i < 8; i++)
        {
            buffer += bin[i + (loopcount * 8)];
        }


        result += (char) (std::stoi(buffer, 0, 2));

        // Clear buffer
        buffer = "";

        loopcount++;

        // Break when all groups of 8 bits are added to result
        if(bin.length() / 8 == loopcount)
        {
            break;
        }
    }


    return result;
}

int Base64::indexof(std::array<char, 64> input, char match)
{
    for(int i = 0; i < input.size(); i++)
    {

        if(input[i] == match)
        {
            return i;
        }

    }
    return -1;
}
