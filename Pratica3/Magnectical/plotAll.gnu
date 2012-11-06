set size square

set style data lines

set terminal png
set output "freefall.png"

plot 'RK1.dat' using 1:2,'RK2.dat' using 1:2,'RK4.dat' using 1:2, 'VelocityVerlet.dat' using 1:2

