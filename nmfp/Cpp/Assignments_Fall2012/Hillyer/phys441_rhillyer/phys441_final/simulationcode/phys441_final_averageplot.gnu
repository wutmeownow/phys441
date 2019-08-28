set terminal png nocrop enhanced font arial 8 size 1000,1000
set output 'averageplot1.png'
set grid

plot "phys441_averages.txt"
