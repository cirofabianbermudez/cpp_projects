#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>

double mandelbrot(std::complex<double> c) {
  // Skiping first iteration 0.0, 0.0
  std::complex<double> zn(c);
  int iter = 45;
  double max_iter = (double)iter;

  for (int n = 0; n < iter; n++) {
    zn = zn * zn + c;
    // std::cout << "DEBUB" << std::endl;
    // std::cout << std::abs(zn) << std::endl;
    if (std::abs(zn) > 2.0) {
      return (double)n;
    }
  }

  return max_iter;
}

int main(int argc, char** argv) {
  double x0 = -0.6;
  double r = 1.2;
  double points = 1000;
  std::complex<double> c;

  // Set fixed-point notation and precision
  std::cout << std::fixed << std::setprecision(5);

  for (double y = -r; y < r; y += (r + r) / (points - 1.0)) {
    for (double x = x0 - r; x < x0 + r; x += (r + r) / (points - 1.0)) {
      c = std::complex<double>(x, y);
      std::cout << std::setw(8) << x << ", " 
                << std::setw(8) << y << ", "
                << std::setw(8) << mandelbrot(c) << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}
