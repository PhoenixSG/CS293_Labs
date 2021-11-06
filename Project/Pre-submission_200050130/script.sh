#! /bin/bash
sudo apt-get install libsfml-dev
# You can choose to comment out the above if you already have the software installed.
g++ -o Mandelbrot Mandelbrot.cpp -lsfml-graphics -lsfml-window -lsfml-system -fopenmp -O2
./Mandelbrot
