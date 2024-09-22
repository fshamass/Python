#include "WaterPouring.hpp"

extern "C" {
    WaterPouring* getWaterPouringInstance(uint8_t jug1Cap, uint8_t jug2Cap, uint8_t targetLevel) {
        return new WaterPouring(jug1Cap, jug2Cap, targetLevel);
    }

    char* getSolution(WaterPouring* instance) {
        char* ret = nullptr;
        if(instance) {
            ret = &(instance->getSolution()[0]);
        }
        return ret;
    }
}