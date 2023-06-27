#!bin/bash

# Source the configuration file.
source ./Scripts/configure.sh

# Remove the contents of the bin folder.
rm -rf bin/*

# Run Cmake, putting the files in the bin directory
cmake -S . -B bin/

# Change to bin/ directory and make the binaries
cd bin/
make

# Change directory back to the top-most directory
cd ..