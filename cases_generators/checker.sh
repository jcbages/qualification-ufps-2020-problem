# gets the largest value for an answer

echo "0" > checker_intermediate
for filename in ../cases_output/*; do
    echo "Checking $filename"
    value=$(cat $filename | sort -n | tail -1)
    echo $value >> checker_intermediate
done

echo "THIS IS THE MAX VALUE: $(cat checker_intermediate | sort -n | tail -1)"
