##=============================================================================
## [Filename]       example.gp
## [Project]        hits_uvc
## [Author]         Ciro Bermudez - cirofabian.bermudezmarquez@ba.infn.it
## [Language]       GNU Makefile
## [Created]        2025/04/02
## [Modified]       -
## [Description]    Makefile tor testing hits_uvc
## [Notes]          -
## [Status]         stable
## [Revisions]      -
##=============================================================================


filename = "output"
file = filename . ".txt"

print "PDF Mode Selected"
reset
unit = 2.5
set terminal pdfcairo size unit*5in, unit*3in font "CMU Serif, 10" fontscale 0.5*unit
set output filename . ".pdf"

xleft = -5; xright = 5; xstep = 1
ydown = -5; yup = 5; ystep = 1
zdown = 0; zup = 1; zstep = 0.1

set xrange [xleft:xright]
set yrange [ydown:yup]
set trange [zdown:zup]

set xtics xleft, xstep*2, xright
set ytics ydown, ystep*2, yup
set ztics zdown, zstep*2, zup


grid_major = 100
grid_minor = 101
set style line grid_major dashtype 1 linecolor rgb "#E0E0E0"
set style line grid_minor dashtype 3 linecolor rgb "#C7C7C7"

set grid front
set mxtics 2; set mytics 2; set mztics 2;
set grid mxtics mytics mztics linestyle grid_major, lines grid_minor
set tics scale 1,1e-3


#set sample 1000
set isosamples 50,50
#set dummy x

# x = variable, u = mean, s = standard deviation
f(x,u,s) = ( 1.0 / sqrt(2 * pi * s**2) ) * exp( ( - (x - u)**2 ) / ( 2 * s**2 ) )

g(y,u,s) = ( 1.0 / sqrt(2 * pi * s**2) ) * exp( ( - (y - u)**2 ) / ( 2 * s**2 ) )

h(x,y) = 10*f(x,0,1) * g(y,0,1)


set size square
set palette gray negative
set cbrange [0:1]

#set view map

splot h(x,y) with pm3d

