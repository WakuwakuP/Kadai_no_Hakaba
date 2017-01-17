#!/bin/bash
printf "Save File Name : "
read FILE
date +"%Y/%m/%d %p %I:%M:%S"
echo 1000
echo 1000 > input
./a < input > result
more input result > $FILE
date +"%Y/%m/%d %p %I:%M:%S"
echo 5000
echo 5000 > input
./a < input > result
more input result >> $FILE
date +"%Y/%m/%d %p %I:%M:%S"
echo 10000
echo 10000 > input
./a < input > result
more input result >> $FILE
date +"%Y/%m/%d %p %I:%M:%S"
echo 30000
echo 30000 > input
./a < input > result
more input result >> $FILE
date +"%Y/%m/%d %p %I:%M:%S"
echo 50000
echo 50000 > input
./a < input > result
more input result >> $FILE
date +"%Y/%m/%d %p %I:%M:%S"
echo 100000
echo 100000 > input
./a < input > result
more input result >> $FILE
date +"%Y/%m/%d %p %I:%M:%S"
rm input
rm result
