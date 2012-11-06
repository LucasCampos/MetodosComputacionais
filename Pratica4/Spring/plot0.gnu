i=0
set term gif animate optimize delay 0 nocrop font "Arial" 10 size 1280, 800; \
set outp "DiagramaDeFaseSpring.gif";
unset key
set xlabel "Posicao"
set ylabel "Velocidade"
set grid
set size square
load 'plot1.gnu'
