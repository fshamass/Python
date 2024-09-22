import sys
sys.path.insert(0,"python")
import water_pouring
import argparse


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description = "Argument parser for water pouring")
    parser.add_argument('jug1_capacity', type=int, help='jug1 capacity')
    parser.add_argument('jug2_capacity', type=int, help='jug2 capacity')
    parser.add_argument('target', type=int, help='target capacity')
    args = parser.parse_args()

    if args.jug1_capacity < 0 or args.jug2_capacity < 0 or args.target < 0:
        print("Invalid arguments. Please run solution --help")
        sys.exit()
    water_pouring.solve(args.jug1_capacity, args.jug2_capacity, args.target)