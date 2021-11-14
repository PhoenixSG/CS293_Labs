#! /bin/bash
wc -l *.cpp *.h | tail --lines 1
g++ -o working_model working_model.cpp -lsfml-graphics -lsfml-window -lsfml-system -fopenmp -O2
if [ $? -ne 0 ]; then
    echo "Failure"
else
    ./working_model
fi