# compile validator in this folder
# g++ -o validator ../validator.cpp

g++-10 -o validator ../validator.cpp
for filename in ../cases/*; do
    echo "Validating $filename"
    ./validator < $filename
done
