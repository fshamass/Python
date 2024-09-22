#include "WaterPouring.hpp"

WaterPouring::WaterPouring(uint8_t jug1Capacity, uint8_t jug2Capacity, uint8_t targetLevel)
  : targetLevel_(targetLevel) {
    //Find min and max jugs capacities and populate internal members
    if(jug1Capacity < jug2Capacity) {
        minJugCapacity_ = jug1Capacity;
        maxJugCapacity_ = jug2Capacity;
        jugsToString[minJugCapacity_] = "jug1";
        jugsToString[maxJugCapacity_] = "jug2";
    } else {
        minJugCapacity_ = jug2Capacity;
        maxJugCapacity_ = jug1Capacity;
        jugsToString[minJugCapacity_] = "jug2";
        jugsToString[maxJugCapacity_] = "jug1";
    }
    std::cout << "min cap: " << std::to_string(minJugCapacity_) << ", max capacity: " << std::to_string(maxJugCapacity_) << std::endl;
}

uint8_t WaterPouring::greatestCommonDivisor(uint8_t cap1, uint8_t cap2) {
    while(cap2 != 0) {
        uint8_t temp = cap2;
        cap2 = cap1 % cap2;
        cap1 = temp;
    }
    return cap1;
}

//Building solution starting with pouring water from source jug to destination jug
void WaterPouring::buildSolution(uint8_t sourceCap, uint8_t destCap,
    std::vector<std::string>& solution) {
    // Initialize intermediate variable that represent current water levels in each jug
    // Start with filling up source jug and keep dest jug empty
    int source = sourceCap;
    int dest = 0;

    // Push 1st step to fill source jug
    solution.push_back(std::string("fill " + jugsToString[sourceCap]));

    // Break the loop when either of the two jugs has target water level
    while ((source != targetLevel_) && (dest != targetLevel_)) {
        // Find the maximum amount that can be poured
        uint8_t temp = std::min(source, destCap - dest);
        solution.push_back(
            std::string("pour " + jugsToString[sourceCap] + " to " + jugsToString[destCap]));

        // Pour "temp" units from source to dest
        dest += temp;
        source -= temp;

        //if any jug reached target level, we have solution. Break out of the loop
        if(source == targetLevel_) {
            if(dest > 0) {
                solution.push_back(std::string("empty " + jugsToString[destCap]));
            }
            break;
        }
        if(dest == targetLevel_) {
            if(source > 0) {
                solution.push_back(std::string("empty " + jugsToString[sourceCap]));
            }
            break;
        }
        // If source jug becomes empty, fill it
        if (source == 0)
        {
            source = sourceCap;
            solution.push_back(std::string("fill " + jugsToString[sourceCap]));
        }
        // If dest jug becomes full, empty it
        if (dest == destCap)
        {
            dest = 0;
            solution.push_back(std::string("empty " + jugsToString[destCap]));
        }
    }
}

bool WaterPouring::isAchievable() {
    bool isSuccess = true;
    //If target water level is greater than max jug capacity,
    //we are unable to measure it with current jugs
    if((targetLevel_ > maxJugCapacity_) ||
       ((minJugCapacity_ == 0) && (maxJugCapacity_ == 0))) {
        isSuccess = false;
    }
    //If target water level does not divide greatest common divisor equally,
    //solution is not possible
    else if(targetLevel_%(greatestCommonDivisor(minJugCapacity_, maxJugCapacity_))) {
        isSuccess = false;
    }
    else {
        //Solution is achievable
    }
    return isSuccess;
}

void WaterPouring::stringifySolution(std::vector<std::string>& solution) {
    //We know solution must have at least one step
    solution_ = solution[0];
    for(size_t i=1; i<solution.size();i++) {
        solution_ += ", " + solution[i];
    }
}

std::string WaterPouring::getSolution() {
    if(!isAchievable()) {
        solution_ = "not achievable";
    } else {
        //Explore solution starting with filling smaller jug
        buildSolution(minJugCapacity_, maxJugCapacity_, minCapacitySolution_);
        //Explore solution starting with filling up larger jug
        buildSolution(maxJugCapacity_, minJugCapacity_, maxCapacitySolution_);
        //From solution from minimum solution steps
        if(maxCapacitySolution_.size() < minCapacitySolution_.size()) {
            stringifySolution(maxCapacitySolution_);
        } else {
            stringifySolution(minCapacitySolution_);
        }
    }
    return solution_;
}