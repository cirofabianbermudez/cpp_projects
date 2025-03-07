##=============================================================================
## [Filename]       mattonella.gp
## [Project]        mattonella
## [Author]         Ciro Bermudez - cirofabian.bermudezmarquez@ba.infn.it
## [Language]       gnuplot 5.4
## [Created]        March 2025
## [Modified]       -
## [Description]    gnuplot script to generate pdf
## [Notes]          -
## [Status]         devel
## [Revisions]      -
##=============================================================================

filename = "mattonella"
input_file = "../data/" . filename . ".txt"

# Terminal configuration
print "PDF Mode Selected"
reset
unit = 2.5
set terminal pdfcairo size unit*5in, unit*3in font "CMU Serif, 10" fontscale 0.5*unit
set output "../output/" . filename . ".pdf"

# Configure range
xleft = 0.0; xright = 7.0; xstep = 1.0
ydown = 0.0; yup    = 7.0; ystep = 1.0

offset = 0.5
set xrange [xleft-offset:xright+offset]
set yrange [ydown-offset:yup+offset]

# Configure grid and ticks
# set xtics xleft, xstep, xright
# set ytics ydown, ystep, yup

# grid_major = 100
# grid_minor = 101
# set style line grid_major dashtype 1 linecolor rgb "#E0E0E0"
# set style line grid_minor dashtype 3 linecolor rgb "#C7C7C7"

# set grid front
# set mxtics 1; set mytics 1; 
# set grid mxtics mytics linestyle grid_major, lines grid_minor
# set tics scale 1,1e-3

unset key

# Disable tics
set tic scale 0

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


# set cbrange [0:1]
set cblabel "Score"
unset cbtics
#set xrange [-0.5:4.5]
#set yrange [-0.5:4.5]
set size square

shift = 0.5

# 2D view
set view map

# Do the plot
#splot input_file using ($1+shift):($2+shift):3 with image
#splot input_file matrix with pm3d
splot input_file matrix with image
