//=============================================================================
// [Filename]       gauss.cpp
// [Project]        gauss
// [Author]         Ciro Bermudez - cirofabian.bermudezmarquez@ba.infn.it
// [Language]       C++ 23
// [Created]        March 2025
// [Modified]       -
// [Description]    C++ code to create gauss sequence
// [Notes]          -
// [Status]         devel
// [Revisions]      -
//=============================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <numbers>
#include <cmath>
#include <cstdio>
#include <format>

// x = variable, mu = mean, sig = standard deviation
double gauss_dist(const double x, const double mu, const double sig){
  double variance = sig*sig;
  double diff = x - mu;
  double arg = - ( diff*diff ) / ( 2.0 * variance );
  double frac = 1.0 / std::sqrt(2.0 * std::numbers::pi * variance) ;
  return frac * std::exp( arg );
}

int main(int argc, char** argv) {

  std::string filename = "../../data/gauss.txt";
  std::ofstream outfile;
  outfile.open(filename);

  double xleft  = -5.0;
  double xright =  5.0;
  double yleft  = -5.0;
  double yright =  5.0;

  double step = 0.5;
  double z = 0.0;

  for (double x = xleft; x <= xright; x += step) {
    for (double y = yleft; y <= yright; y += step) {
      z = gauss_dist(x, 0.0, 1.0) * gauss_dist(y, 0.0, 1.0);
      // 7 total digits, 3 digits after decimal point
      outfile << std::format("{:>7.3f} {:>7.3f} {:>7.3f}\n", x, y, z);
    }
    outfile << std::endl;
  }

  outfile.close();

  return 0;
}
