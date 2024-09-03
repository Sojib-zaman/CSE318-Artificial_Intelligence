#!/bin/bash
rm -f test_graph.txt

g++ -o ok 1905067_graph.cpp
for ((i=1; i < 99; i++)); do
    ./ok $i >> test_graph.txt
done
gnuplot plot.plt