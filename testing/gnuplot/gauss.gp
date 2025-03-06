##=============================================================================
## [Filename]       gauss.gp
## [Project]        gauss
## [Author]         Ciro Bermudez - cirofabian.bermudezmarquez@ba.infn.it
## [Language]       gnuplot 5.4
## [Created]        March 2025
## [Modified]       -
## [Description]    gnuplot script to generate pdf
## [Notes]          -
## [Status]         devel
## [Revisions]      -
##=============================================================================

filename = "gauss"
input_file = "../data/" . filename . ".txt"

# Terminal configuration
print "PDF Mode Selected"
reset
unit = 2.5
set terminal pdfcairo size unit*5in, unit*3in font "CMU Serif, 10" fontscale 0.5*unit
set output "../output/" . filename . ".pdf"

# Calculate stats
stats input_file using 3 nooutput

# Configure range
xleft = -5.0; xright = 5.0; xstep = 1.0
ydown = -5.0; yup    = 5.0; ystep = 1.0
zdown =  STATS_min; zup    = STATS_max; zstep = (STATS_max-STATS_min)/10

set xrange [xleft:xright]
set yrange [ydown:yup]
set zrange [zdown:zup]

# Configure grid and ticks
set xtics xleft, xstep*2, xright
set ytics ydown, ystep*2, yup
set ztics zdown, zstep*2, zup

grid_major = 100
grid_minor = 101
set style line grid_major dashtype 1 linecolor rgb "#E0E0E0"
set style line grid_minor dashtype 3 linecolor rgb "#C7C7C7"

# set grid front
set grid
set mxtics 2; set mytics 2; set mztics 2;
set grid mxtics mytics mztics linestyle grid_major, lines grid_minor
set tics scale 0.1,0.1,0.1

# x = variable, u = mean, s = standard deviation
#f(x,u,s) = ( 1.0 / sqrt(2 * pi * s**2) ) * exp( ( - (x - u)**2 ) / ( 2 * s**2 ) )
#g(y,u,s) = ( 1.0 / sqrt(2 * pi * s**2) ) * exp( ( - (y - u)**2 ) / ( 2 * s**2 ) )
#h(x,y) = 10*f(x,0,1) * g(y,0,1)

unset key

set size square

# Color palette
#set palette rgb 2,22,2 negative;
#set palette model RGB
#set palette gray negative

# Hide color indicator
#unset colorbox

# Color palette
#set palette gray negative
# Viridis color palette
# https://waldyrious.net/viridis-palette-generator/
set palette defined ( \
    0.00  0.2670  0.0049  0.3294, \
    0.15  0.2291  0.3224  0.5457, \
    0.30  0.1276  0.5669  0.5506, \
    0.45  0.3692  0.7889  0.3829, \
    0.60  0.6785  0.8637  0.1895, \
    0.75  0.9329  0.8405  0.1278, \
    1.00  0.9932  0.9062  0.1439) 

# Redefine min and max values
set cbrange [STATS_min:STATS_max]

# 2D view
set view map

# Do the plot
splot input_file using 1:2:3 with pm3d
#splot input_file using 1:2:3 with image

