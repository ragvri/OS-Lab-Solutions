#!/bin/bash
# Making 3 arrays namely a,b,c; a contains the first n/3 elements of the fibonacci series, b the next n/3 and c contains the last n/3 elements.
# then every element of c is added element wise to every element of a and then b is concatenated in the output
echo "Input n which is multiple of 3"
read n
echo $n
i=2
first=0
second=1
a[0]=0
a[1]=1
echo "The fibonacci sequence is:"
echo -n 0 1" "
# making the first array a
while [ $i -lt $((n/3)) ]; do
	a[$i]=$((first+second))
	echo -n ${a[$i]}" "
	first=$second
	second=${a[$i]}
	i=$i+1
done 
i=0
# making the second array b
while [ $i -lt $((n/3)) ]; do 
	b[$i]=$((first+second))
	echo -n ${b[$i]}" "
	first=$second
	second=${b[$i]}
	i=$((i+1))
done
i=0
# making the third array c
while [ $i -lt $((n/3)) ]; do
	c[$i]=$((first+second))
	echo -n ${c[$i]}" "
	first=$second
	second=${c[$i]}
	i=$((i+1))
done
i=0
# adding every element of c to corresponding element of a
echo " "
echo "The segment after adding is"
while [ $i -lt $((n/3)) ]; do
	a[$i]=$((a[$i]+c[$i]))
	echo -n ${a[$i]}" "
	i=$((i+1))
done
i=0
# printing the result after concatenating
echo " "
echo "The segment after concatenation is"
while [ $i -lt $((n/3)) ]; do
	echo -n ${a[$i]}" "
	i=$((i+1))
done
i=0
while [ $i -lt $((n/3)) ]; do
	echo -n ${b[$i]}" "
	i=$((i+1))
done
echo " "
