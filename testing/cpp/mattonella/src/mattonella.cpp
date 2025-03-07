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
#include <array>

template<typename T, std::size_t Rows, std::size_t Cols>
void printMatrix(const std::array<std::array<T, Cols>, Rows>& matrix, bool invertRows = true) {
  double value = 0.0;
  
  if (invertRows) {

    // Print rows in reverse order (botton to top)
    for (std::size_t i = Rows; i-- > 0;) {
      for (std::size_t j = 0; j < Cols; ++j) {
        value = static_cast<double>( matrix[i][j] );
        std::cout << std::format("{:>7.2f} ", value);
      }
      std::cout << "\n";
    }

  } else {

    // Print rows in normal order (top to bottom)
    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < Cols; ++j) {
        value = static_cast<double>( matrix[i][j] );
        std::cout << std::format("{:>7.2f} ", value);
      }
      std::cout << "\n";
    }

  }

}

//argc, char** argv
int main() {

  std::string filename = "../../data/mattonella.txt";
  std::ofstream outfile;
  outfile.open(filename);

  // Random number generator
  std::random_device rd;      // Non-deterministic source (seed)
  std::mt19937 gen(rd());     // Seed the generator

  // Dimensions of the mattonella
  const std::size_t x_dim = 8;
  const std::size_t y_dim = 8;

  // Create mattonella matrix
  std::array<std::array<double, x_dim>, y_dim> mattonella {0.0};
  
  // Define a uniform distribution
  //std::uniform_real_distribution<> dist(0.0, 1.0);
  //std::uniform_int_distribution<> dist(0, 1);
  std::uniform_int_distribution<> uniform_dist(4, 5);
  
  // Define the Gaussian distribution mean = 0.0, std = 1.0
  std::normal_distribution gauss_dist(0.0, 0.8);
  //std::normal_distribution gauss2(0.0, 1.0);
 
  // for (std::size_t i = 0; i < mattonella.size(); ++i) {
  //   for (std::size_t j = 0; j < mattonella[i].size(); ++j) {
  //       mattonella[i][j] = 10.0*(i+1) + j+1;
  //   }
  // }
  
  printMatrix(mattonella);

  // Generate random hit
  int rand_x = uniform_dist(gen);
  int rand_y = uniform_dist(gen);
  
  std::cout << std::format("\nrand_x: {:>2d},  rand_y: {:>2d}\n", rand_x, rand_y);

  // Generate random numbers to spread
  double x_dist;
  double y_dist;
  double offset = 0.5;
  
  // Indexes
  std::size_t idx_x = 0;
  std::size_t idx_y = 0;
  for (int i = 0; i < 10000; i++) {
    x_dist = static_cast<double>(rand_x) + offset + gauss_dist(gen);
    y_dist = static_cast<double>(rand_y) + offset + gauss_dist(gen);
    //std::cout << std::format("x_dist: {:>5.2f},  y_dist: {:>5.2f}\n", x_dist, y_dist );
    idx_x = static_cast<std::size_t>(std::floor(x_dist));
    idx_y = static_cast<std::size_t>(std::floor(y_dist));
    mattonella[idx_y][idx_x] = mattonella[idx_y][idx_x] + 1;
  }
  
  printMatrix(mattonella);
  std::cout << std::format("\nrand_x: {:>2d},  rand_y: {:>2d}\n", rand_x, rand_y);

  int value = 0;
  for (int x = 0; x < static_cast<int>(x_dim); x++) {
    for (int y = 0; y < static_cast<int>(y_dim); y++) {
      // 7 total digits, 3 digits after decimal point
      if (x == rand_x && y == rand_y) {
        value = 1;
      } else {
        value = 0;
      }
      outfile << std::format("{:>3d} {:>3d} {:>3}\n", x, y, value);
    }
    outfile << "\n";
  }

  outfile.close();

  return 0;
}
