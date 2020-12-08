# make cases online
# g++ -o online ../online.cpp

g++-10 -o online ../online.cpp
for filename in ../cases/*; do
    echo "Converting to online $filename"
    out="$(basename $filename)"
    ./online < $filename > ../final_cases/$out
done
