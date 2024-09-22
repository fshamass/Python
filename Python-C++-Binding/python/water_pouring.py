from ctypes import *
import sys

def solve(jug1_capacity, jug2_capacity, target):
    try:
        water_pouring_lib = CDLL("lib/libwaterpouring.so")
    except:
        print('Error: Failed to load library')
        sys.exit()

    water_pouring_class = water_pouring_lib.getWaterPouringInstance
    water_pouring_class.argtypes = [c_ubyte,c_ubyte,c_ubyte]
    water_pouring_class.restype = c_void_p
    water_pouring_instance = c_void_p(water_pouring_class(jug1_capacity, jug2_capacity, target))

    water_pouring_solution = water_pouring_lib.getSolution
    water_pouring_solution.restype = c_char_p
    print('Solution is: {}'.format(water_pouring_solution(water_pouring_instance)))

