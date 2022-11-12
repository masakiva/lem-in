#!/bin/bash

MAP="maps/subject3.map"
if [ $1 != 0 ]
then
	MAP=$1
fi
make
echo "---- ["$MAP"] ----"
cat $MAP
echo "---- [lem-in] ----"
./lem-in -v < $MAP 

