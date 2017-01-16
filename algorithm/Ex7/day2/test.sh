#!/bin/sh
echo 1 > input
echo 1000 >> input
./a < input > result
more input result > result.txt
echo 1 > input
echo 5000 >> input
./a < input > result
more input result >> result.txt
echo 1 > input
echo 10000 >> input
./a < input > result
more input result >> result.txt
echo 2 > input
echo 1000 >> input
./a < input > result
more input result >> result.txt
echo 2 > input
echo 5000 >> input
./a < input > result
more input result >> result.txt
echo 2 >input
echo 10000 >> input
./a < input > result
more input result >> result.txt
echo 3 > input
echo 1000 >> input
./a < input > result
more input result >> result.txt
echo 3 > input
echo 5000 >> input
./a < input > result
more input result >> result.txt
echo 3 > input
echo 10000 >> input
./a <input > result
more input result >> result.txt
rm input
rm result
