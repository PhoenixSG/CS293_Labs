#! /bin/bash
# sudo apt-get install libsfml-dev
# You can choose to comment out the above if you already have the software installed.
wc -l *.cpp *.h | tail --lines 1
g++ -o working_model working_model.cpp -lsfml-graphics -lsfml-window -lsfml-system -fopenmp -O2
if [ $? -ne 0 ]; then
    echo "Failure"
else
    ./working_model
fi