# Author: Ciro Fabian Bermudez Marquez
# File: collatz.gp
# Description: collatz
# Run: gnuplot collatz.gp

filename = "collatz"
file = filename . ".txt"
select = 1

# Change the terminal from the command line
if (ARGC >= 1) {
    select = ARG1 + 0
}

if (select == 1) {
# PNG Version
  print "PNG Mode Selected"
  reset
  unit = 3
# 'gray75'
  set terminal pngcairo size unit*640, unit*384 font "CMU Serif, 10" fontscale 1*unit*0.95 background rgb "#000000" 
  set output filename . ".png"
}
if (select == 2) {
# PDF Version
  print "PDF Mode Selected"
  reset
  unit = 2.5
  set terminal pdfcairo size unit*5in, unit*3in font "CMU Serif, 10" fontscale 0.5*unit
  set output filename . ".pdf"
}

# Disable x-axis
unset xtics
unset xlabel

# Disable y-axis
unset ytics
unset ylabe

# Disable the border completely
set border 0

# Disable legend
unset key

graph_style = 102
set style line graph_style linecolor rgb "#ffffff"\
                                     linewidth 0.1 \
#                                     dashtype  1 \
#                                     pointsize 1 \
#                                     pointtype 4 \

plot file index 1:1000 with lines linestyle graph_style

# Restore default values
reset
set terminal qt
set output

