# compile generator in this folder
# g++ -o generator ../generator.cpp

# change filename to reflect sm, md, lg
# also change params in generator and recompile for each case
# used params can be found in random_params.txt

seed=987654321
total=20
for (( i=0, seed=987654321; i<total; i++, seed++ )) do
    # print the seed being used
    echo "Using seed: $seed"
    # generates an input
    ./generator $seed > ../cases/random_lg_$total_$i
done
