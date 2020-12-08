# compile solution in this folder
# g++ -o solution ../solution.cpp

g++-10 -o solution ../solution.cpp
for filename in ../cases/*; do
    echo "Running $filename"
    out="$(basename $filename)"
    ./solution < $filename > ../cases_output/$out
done
