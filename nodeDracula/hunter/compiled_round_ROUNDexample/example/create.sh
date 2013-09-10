#!/bin/sh

for (( c=0; c < 4; c++ )); 
do 
	gcc -o ../hunter$c game.c mrDrunk.c HunterView.c Graph.c -ljansson; 
done
