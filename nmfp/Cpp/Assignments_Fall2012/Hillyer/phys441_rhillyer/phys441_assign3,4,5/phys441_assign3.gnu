set terminal png nocrop enhanced font arial 8 size 1000,1000
set output 'assign3.png'
set grid
set xrange [0:20]
y(x) = 0.156201+0.0218963*x-0.00145874*x**2+5.33896e-05*x**3
plot y(x)
#plot "phys441_data.txt"
