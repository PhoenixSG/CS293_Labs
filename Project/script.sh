#! /bin/bash
g++ -o working_model working_model.cpp -lsfml-graphics -lsfml-window -lsfml-system -fopenmp -O2
./working_model