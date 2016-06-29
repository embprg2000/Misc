#!/bin/bash

# Simple little script to practice spanish numbers.

# To install espeak
# sudo apt install espeak
# e.g. espeak -v es "4567"

function randomNum()
{
	echo $(( $RANDOM % 100000 ));
}

function speak
{
	espeak -v es $1

	read guess
	if [ $guess == $1 ]; then
		echo "Good"
	elif [ $guess == "" ]; then
		echo "Stop"
	elif [ $guess == "?" ]; then
		echo $1
	else
		echo "false"
	fi
}

res="Start"
num=$( randomNum )

while [ $res != "Stop" ]; do
	res=$( speak $num )

	echo $res

	if [ $res == "Good" ]; then
		num=$( randomNum )
	fi
done

