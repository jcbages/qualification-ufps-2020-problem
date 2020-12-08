# compile solution in this folder
# g++ -o solution ../solution.cpp
# remember to uncomment online only lines in solution file

g++-10 -o solution ../solution.cpp
for filename in ../final_cases/*; do
    echo "Running $filename"
    out="$(basename $filename)"
    ./solution < $filename > ../final_cases_output/$out
done
