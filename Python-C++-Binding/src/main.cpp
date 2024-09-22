

#include <string.h>
#include <iostream>
#include <cstdlib>
#include "WaterPouring.hpp"

void printInvalidArgs() {
        std::cout << "Invalid command. Please use --help for usage" << std::endl;
}

bool checkNumValid(int num) {
    if((num >= 1) && (num <= 255)) {
        return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    //Check if help command
    if((argc == 2) && (strcmp(argv[1],"--help")==0)) {
        std::cout << "usage: "
            "water_pouring --jug1_capacity <num> --jug2_capacity <num> --target <num>" << std::endl;
        std::cout << "<num> is any value between 1-255" << std::endl;
    } else if(argc == 7) {
        int jug1Cap, jug2Cap,target;
        if((strcmp(argv[1],"--jug1_capacity")==0) && (strcmp(argv[3],"--jug2_capacity")==0) &&
            (strcmp(argv[5],"--target")==0)) {
            jug1Cap = atoi(argv[2]);
            jug2Cap = atoi(argv[4]);
            target = atoi(argv[6]);
            if((checkNumValid(jug1Cap)) && (checkNumValid(jug2Cap)) && (checkNumValid(target))) {
                WaterPouring waterPouring(static_cast<uint8_t>(jug1Cap),
                    static_cast<uint8_t>(jug2Cap), static_cast<uint8_t>(target));
                std::cout << "Solution is: " << waterPouring.getSolution() << std::endl;
            } else {
                printInvalidArgs();
            }
        } else {
            printInvalidArgs();
        }
    } else {
        printInvalidArgs();
    }
    return 0;
}
