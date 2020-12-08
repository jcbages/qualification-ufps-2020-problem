# compare offline and online outputs
for filename in ../cases/*; do
    echo "Checking online offline $filename"
    out="$(basename $filename)"
    diff ../cases_output/$out ../final_cases_output/$out || break
done
