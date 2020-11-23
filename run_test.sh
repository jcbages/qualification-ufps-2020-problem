# This small script comes handy when testing small cases
# Make sure you set the generator bounds to small values
# as otherwise the brute solution may take too long to execute
# This script does the following an infinite number of times:
#  1 compiles the solution.cpp, brute.cpp, and solution.cpp
#  2 generates an input using the generator
#  3 run the solution using the input from the generator
#  4 run the brute solution using the input from the generator
#  5 compare both outputs, if they are the same, go to step 1, else break
# If the program breaks, it will show the seed used to generate the input
# So that you can create the bad case deterministically from the generator
# 
# Usage ./run_test.sh [-s <from_seed>] [-c] [-j] [-p]

# Define default values for variables
cpp=0
java=0
python=0
from_seed=0

# Read from flags in case defaults were changed
while getopts s:cjp flag; do
    case "${flag}" in
        s) from_seed=${OPTARG};;
        c) cpp=1;;
        j) java=1;;
        p) python=1;;
        ?) exit;;
    esac
done

echo "Arguments: cpp:$cpp java:$java python:$python from_seed:$from_seed"

# Create a folder for inputs and outputs
folder="test"
mkdir -p $folder
echo "Attempted to create folder $folder"

# Compile the solution, brute, and generator
g++-10 brute.cpp -o brute
g++-10 generator.cpp -o generator
if [ $cpp -eq 1 ]; then g++-10 solution.cpp -o solution; fi
if [ $java -eq 1 ]; then javac solution.java; fi

mv brute $folder/brute
mv generator $folder/generator
if [ $cpp -eq 1 ]; then mv solution $folder/solution; fi
if [ $java -eq 1 ]; then mv *.class $folder/; fi
echo "Finished compiling files"

# run an infinite number of times
for (( seed=$from_seed; ; seed++ )) do
    # print the seed being used
    echo "Using seed: $seed"
    # generates an input
    ./$folder/generator $seed > $folder/inp
    # run the solution with the generated input 
    if [ $python -eq 1 ]; then python3 solution.py < $folder/inp > $folder/out1_py; fi
    if [ $java -eq 1 ]; then java -cp $folder Main < $folder/inp > $folder/out1_jv; fi
    if [ $cpp -eq 1 ]; then ./$folder/solution < $folder/inp > $folder/out1_cp; fi
    # run the brute with the generated input
    ./$folder/brute < $folder/inp > $folder/out2
    # compare and break if different outputs were obtained (comment out the ones you don't need)
    if [ $python -eq 1 ]; then diff $folder/out1_py $folder/out2 || break; fi
    if [ $java -eq 1 ]; then diff $folder/out1_jv $folder/out2 || break; fi
    if [ $cpp -eq 1 ]; then diff $folder/out1_cp $folder/out2 || break; fi
done
