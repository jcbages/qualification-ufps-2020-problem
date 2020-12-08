for filename in ../cases/*; do
    echo "Validating $filename"
    ./validator < filename
done