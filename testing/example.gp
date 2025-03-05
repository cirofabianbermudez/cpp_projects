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


filename = "data"
file = filename . ".txt"

print "PDF Mode Selected"
reset
unit = 2.5
set terminal pdfcairo size unit*5in, unit*3in font "CMU Serif, 10" fontscale 0.5*unit
set output filename . ".pdf"
legend = ""


xleft = 0; xright = 8; xstep = 1
ydown = 0; yup = 8; ystep = 1

offset = 0.0

set xrange [xleft-offset:xright+offset]
set yrange [ydown-offset:yup+offset]

#set xtics xleft-offset,offset,xright+offset
#set ytics ydown-offset,offset,yup+offset


grid_major = 100
grid_minor = 101
set style line grid_major dashtype 1 linecolor rgb "#E0E0E0"
set style line grid_minor dashtype 3 linecolor rgb "#C7C7C7"

set grid front
set mxtics 1; set mytics 1; 
set grid mxtics mytics linestyle grid_major, lines grid_minor
set tics scale 1,1e-3


unset key
set tic scale 0
#set palette gray
#set palette defined (0 "black", 1 "white")
#set palette rgbformula -7,2,-7

set palette gray negative
set cbrange [0:1]
set cblabel "Score"
unset cbtics
#set xrange [-0.5:4.5]
#set yrange [-0.5:4.5]
set size square

shift = 0.5

plot file using ($1+shift):($2+shift):3 with image
