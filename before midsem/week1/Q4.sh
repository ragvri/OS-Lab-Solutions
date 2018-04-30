#!/bin/bash

# assuming one sentence means one line.

cd os 	#changing directory to os
a=$(ls -S -r) #a now has a string which contains the file names in ascending order
array=(${a}) #converting the string to array

i=1
length=${#array[@]} #gets the length of array

emptyfile=${array[0]} # gets the name of emptyfile
while [ $i -lt $((length)) ]
do
	firstline=$(cat ${array[$i]} | head -1) 
	# firstline=$(head -n 1 ${array[$i]}) # the value after -n tells how many lines we want of filename specified by the array
	echo $firstline>>$emptyfile # appends the line to the emptyfile.
	i=$((i+1))
done

	