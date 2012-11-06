set xrange [-3:3]
set yrange [-3:3]
n=5000  # n present here the number of blocks in your file
plot "PV.dat" using 1:2 every :::i::i
i=i+1
if (i<n) reread
set output; \
set term pop
