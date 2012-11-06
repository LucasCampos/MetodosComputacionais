set size square

set style data lines

set terminal png
set output "freefall.png"

plot 'RK1.dat' using 1:3,'RK2.dat' using 1:3,'RK4.dat' using 1:3, 'VelocityVerlet.dat' using 1:3

