#!bin/bash

# Source the configuration file.
source ./Scripts/configure.sh

# Run Cmake, putting the files in the bin directory
cmake -S . -B bin/

# Change to bin/ directory and make the binaries
cd bin/
make

# Change directory back to the top-most directory
cd ..