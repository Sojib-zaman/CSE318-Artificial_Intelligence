set terminal pngcairo enhanced font "arial,12" size 800,600
set output 'test_graph.png'


set title "Training Data Size vs. Mean Accuracy"
set xlabel "Training Data Size"
set ylabel "Mean Accuracy"

set key font "Times New Roman,12"
set grid
set grid linecolor rgb "gray"


set key right top
set xrange [0:100]

plot "test_graph.txt" using 1:2 with linespoints ls 1 title "Mean Accuracy vs Train data perchantage"
