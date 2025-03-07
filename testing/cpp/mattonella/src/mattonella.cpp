//=============================================================================
// [Filename]       mattonella.cpp
// [Project]        mattonella
// [Author]         Ciro Bermudez - cirofabian.bermudezmarquez@ba.infn.it
// [Language]       C++ 23
// [Created]        March 2025
// [Modified]       -
// [Description]    C++ code to create mattonella sequence
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
#include <random>

int main(int argc, char** argv) {

  std::string filename = "../../data/mattonella.txt";
  std::ofstream outfile;
  outfile.open(filename);

  // Random number generator
  std::random_device rd;      // Non-deterministic source (seed)
  std::mt19937 gen(rd());     // Seed the generator

  // Dimensions of the mattonella
  int x_dim = 8;
  int y_dim = 8;
  
  // Define a uniform distribution
  //std::uniform_real_distribution<> dist(0.0, 1.0);
  std::uniform_int_distribution<> dist(0, 1);
  
  // Define the Gaussian distribution
  //std::normal_distribution gauss1(0.0, 1.0);
  //std::normal_distribution gauss2(0.0, 1.0);
  
  //double x_dist = gauss1(gen);
  //double y_dist = gauss2(gen);
  
  int random_number = dist(gen);

  for (int x = 0; x < x_dim; x++) {
    for (int y = 0; y < y_dim; y++) {
      // 7 total digits, 3 digits after decimal point
      outfile << std::format("{:>3d} {:>3d} {:>3}\n", x, y, dist(gen));
    }
    outfile << std::endl;
  }

  outfile.close();

  return 0;
}
