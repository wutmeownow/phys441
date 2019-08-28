set terminal png nocrop enhanced font arial 8 size 1000,1000
set output 'assign6.png'
set grid
set xrange [0:5]
set yrange [0:1]
y(x) = .168054*x / (-1.253 + x)
plot "phys441_assign6_data.txt", y(x)
