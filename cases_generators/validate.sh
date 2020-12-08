# compile validator in this folder
# g++ -o validator ../validator.cpp

for filename in ../cases/*; do
    echo "Validating $filename"
    ./validator < $filename
done
