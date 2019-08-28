set terminal png nocrop enhanced font arial 8 size 500,500
set output 'assign8.png'
set grid
#set xrange [0:1200]
#set yrange [0:300]
plot "phys441_assign8_data.txt"
