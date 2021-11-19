#! /bin/bash
sudo apt-get install libsfml-dev
# You can choose to comment out the above if you already have the software installed.
g++ -o main_working_model main_working_model.cpp -lsfml-graphics -lsfml-window -lsfml-system -fopenmp -O2
if [ $? -ne 0 ]; then
    echo "Failure"
else
    ./main_working_model
fi
