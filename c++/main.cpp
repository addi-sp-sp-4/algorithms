#include <iostream>
#include "Base64.h"

int main(int argc, char *argv[]) {

    if(argc < 3)
    {
        std::cout << "Invalid argument length.\n";
        return 0;
    }

    if(std::string(argv[1]) == "decode")
    {
        std::cout << "\nFunction decode:\n";
        for(int i = 2; i < argc; i++)
        {
            std::cout << "Input: " << argv[i] << "\nOutput: " << Base64::decode(argv[i]) << "\n";
        }
    }

    else if(std::string(argv[1]) == "encode")
    {
        std::cout << "\nFunction encode:\n";

        for(int i = 2; i < argc; i++)
        {
            std::cout << "Input: " << argv[i] << "\nOutput: " << Base64::encode(argv[i]) << "\n";
        }
    }
    else
    {
        std::cout << "Unsupported argument, use either 'decode' or 'encode'\n";
    }
    return 0;

}