set terminal png nocrop enhanced font arial 8 size 1000,1000
set output 'plot1.png'
set grid

set xrange[0:1500]

#width = 1
#hist(x,width) = width*floor(x/width)+width/2.0

maxwell_boltz_func(x) = (sqrt((2/pi)*((6.63e-26)/(1.3806e-23*273))**3)*(x)**2*exp((-6.63e-26*x**2)/(2*1.3806e-23*273)))*100

avg = sqrt(8*8.314472*273/(pi*.039948))

set label 1 gprintf("Average = %g", avg) at 1000,2000

#plot "vmagF.txt" u (hist($1,width)):(1.0) smooth freq w boxes lc rgb"pink" notitle

plot "histogram_vmagF.txt" smooth freq w boxes lc rgb"pink" notitle, maxwell_boltz_func(x) lc rgb"blue"
#plot maxwell_boltz_func(x) lc rgb"blue"
