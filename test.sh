#!/bin/bash

MAP="maps/no_ant_maps/simple.map"
if [ $1 != 0 ]
then
	MAP=$1
fi
make
cat $MAP
echo "---------------------"
./lem-in < $MAP 

