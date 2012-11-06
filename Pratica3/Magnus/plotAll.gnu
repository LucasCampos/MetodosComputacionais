set size square

set style data lines

set terminal png
set output "Magnus.png"

plot 'RK1.dat','RK2.dat','RK4.dat', 'VelocityVerlet.dat'

