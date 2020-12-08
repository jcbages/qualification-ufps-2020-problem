# compile validator in this folder
# g++ -o validator ../validator.cpp

g++-10 -o validator ../validator.cpp
for filename in ../final_cases/*; do
    echo "Validating online $filename"
    ./validator < $filename
done
