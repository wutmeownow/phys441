set terminal png nocrop enhanced font arial 8 size 1000,1000
set output 'deltah.png'
set grid
set xrang [10e-20:1]
deltah(x) = abs(2-((1+x)**2-1**2)/(x))
plot deltah(x)
