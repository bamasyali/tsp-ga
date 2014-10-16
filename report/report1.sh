#!/bin/bash
# Set the field seperator to a newline
IFS="
"
# Loop through the file
for line in `cat seed.txt`;do
# Echo the line (echo could be changed to whatever command you want)
./genetic 50 0.5 1 1 $line >> report1swap.csv
./genetic 50 0.5 1 1 $line >> report1insert.csv
./genetic 50 0.5 1 1 $line >> report1inversion.csv
./genetic 50 0.5 1 1 $line >> report1random.csv
done
