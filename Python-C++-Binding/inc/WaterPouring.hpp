#ifndef WATER_POURING_HPP
#define WATER_POURING_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

//Class to implementing solution for water pouring puzzle
//Class does not generate any exceptions
//All capacities were presented by 8 bit variables which mounts for max 255 liters
//Max 255 liters seems reasonable and would reduce memory consumption if larger variables are used
class WaterPouring {
public:
    //Set the initial capacities of the 2 jugs and the target level
    WaterPouring(uint8_t jug1Capacity, uint8_t jug2Capacity, uint8_t targetLevel);
    ~WaterPouring() = default;
    //String output of the solution
    std::string getSolution();
private:
    //Method to check if the solution is achievable
    bool isAchievable();
    //Method to calculate the greatest common divisor
    uint8_t greatestCommonDivisor(uint8_t cap1, uint8_t cap2);
    //Method to form solution
    void buildSolution(uint8_t sourceCap, uint8_t destCap, std::vector<std::string>& solution);
    //Form solution as string
    void stringifySolution(std::vector<std::string>& solution);
    //Holds steps for starting with min capacity jug
    std::vector<std::string> minCapacitySolution_;
    //Holds steps for starting with max capacity jug
    std::vector<std::string> maxCapacitySolution_;
    //Minimum capacity jug
    uint8_t minJugCapacity_;
    //Maximum jug capacity
    uint8_t maxJugCapacity_;
    //Target Level needed
    uint8_t targetLevel_;
    //Solution string
    std::string solution_;
    //Map from min and max capacity to jugs pass in construction
    std::unordered_map<uint8_t, std::string> jugsToString;

};
#endif
