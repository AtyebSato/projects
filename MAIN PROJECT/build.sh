#!/bin/bash

g++ main.cpp bullet.cpp functions.cpp assets.cpp logic.cpp globals.cpp enemies.cpp -o game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

if [ $? -eq 0 ]; then
    echo "Build succeeded. Running game..."
    ./game
else
    echo "Build shat itself."
fi
