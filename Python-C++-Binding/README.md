Coding Assessment for Water Pouring Puzzle
The setup is designed to run on Linux based machine. I have tried it on my MacBook Pro.
Assumptions: machine has GNU Compiler g++ installed and python version 2.7 and beyond

Assessment instructions was to generate executable and python package to exercise the solution
To generate executable:
 - In the main directory and run following command
 make exec
 - Executable water_pouring will be generated in main directory
 - Executable can be run with following options as requested by instruction
  water_pouring --help
    Prints out the options for running the command
  ./water_pouring --jug1_capacity 5 --jug2_capacity 3 --target 4
    Prints the sequence of actions taken to arrive at the target

To use Python script:
Package ctypes is used to bind python with c++ and it is part of Python standard library. No need
for additional installation. To use Python script
 - In the main directory and run following command
 make shared
- New directory "lib" will be created and resulting library will be placed there.
- In main directory, run following command
  python3 solution.py <jug1_capacity> <jug2_capacity> <target>
  solution.py script calls script "water_pouring.py" and calls resolve method to solve puzzle as it
  has been requested by the instructions
