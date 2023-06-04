#ifndef DICE_H
#define DICE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>

namespace dice{

    class die{
        private:
            int size;      
            //std::random_device rd; //this is what should go inside mt(), but there's a bug in the gcc compilter that causes random_engine to only return 0 so I'm using the system time as the seed for mt.
            std::mt19937 mt; //A pseudo-random number generator
            std::uniform_int_distribution<int> distribution; //A map for the generator

        public:

            die() = default;

            die(int size_in):
                size{size_in}, mt(std::time(nullptr)), distribution(1, size) {} //Seeds the generator using system time, then sets the map size
            ~die(){}

            int roll();
};

}

#endif