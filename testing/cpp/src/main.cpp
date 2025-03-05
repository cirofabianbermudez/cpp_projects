//=============================================================================
// [Filename]       main.cpp
// [Project]        uart_ip
// [Author]         Ciro Bermudez - cirofabian.bermudez@gmail.com
// [Language]       C++ 17
// [Created]        Jan 2025
// [Modified]
// [Description]    C++ code to perform UART communication
// [Notes]          This project uses this library
//                  https://github.com/wjwwood/serial
// [Status]         stable
// [Revisions]
//=============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <numbers>

#include <cstdio>

double gauss_dist(const double x, const double mu, const double sig){
  double variance = sig*sig;
  double diff = x - mu;
  double arg = ( - diff*diff ) / ( 2.0 * variance );
  double frac = 1.0 / std::sqrt(2 * std::numbers::pi * variance) ;

  return frac * std::exp( arg );
}

int main(int argc, char** argv) {



  return 0;
}
