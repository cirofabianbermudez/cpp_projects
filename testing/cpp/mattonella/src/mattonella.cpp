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
#include <vector>

template<typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix, bool invertRows = true, std::ostream& out = std::cout) {
  double value = 0.0;

  // matrix[rows][columns]
  // matrix[  i ][  j  ]
  // matrix[  y ][  x  ]
  
  std::size_t Rows = matrix.size();
  std::size_t Cols = !matrix.empty()? matrix[0].size() : 0;
  
  if (invertRows) {

    // Print rows in reverse order (botton to top)
    for (std::size_t i = Rows; i-- > 0;) {
      for (std::size_t j = 0; j < Cols; ++j) {
        value = static_cast<double>( matrix[i][j] );
        out << std::format("{:>7.2f} ", value);
      }
      out << "\n";
    }

  } else {

    // Print rows in normal order (top to bottom)
    for (std::size_t i = 0; i < Rows; ++i) {
      for (std::size_t j = 0; j < Cols; ++j) {
        value = static_cast<double>( matrix[i][j] );
        out << std::format("{:>7.2f} ", value);
      }
      out << "\n";
    }
    
  }

}

int main(int argc, char* argv[]) {
  
  // Parse command line arguments
  if (argc < 3) {
    std::cerr << "Error:\n Usage: " << argv[0] << " <x_dim> <y_dim>\n";
    return 1;
  }

  // Pixel matrix dimensions 
  int x_dim = 0;
  int y_dim = 0;

  try {
    x_dim = std::stoi(argv[1]);
    y_dim = std::stoi(argv[2]);
    if (x_dim <= 0 || y_dim <= 0) {
      throw std::invalid_argument("Size must be a positive integer.");
    }
  } catch (const std::invalid_argument& e) {
    std::cerr << "Invalid input: " << e.what() << '\n';
    return 1;
  } catch (const std::out_of_range& e) {
    std::cerr << "Input out of range: " << e.what() << '\n';
    return 1;
  }
  
  std::cout << std::format("x_dim: {:>2d},  y_dim: {:>2d}\n", x_dim, y_dim);

  // Define output file
  std::string filename = "../../data/mattonella.txt";
  std::ofstream outfile;
  outfile.open(filename);

  // Random number generator
  std::random_device rd;      // Non-deterministic source (seed)
  std::mt19937 gen(rd());     // Seed the generator

  // Create mattonella matrix
  std::vector<std::vector<double>> pixel_matrix(y_dim, std::vector<double>(x_dim, 0.0));
  printMatrix(pixel_matrix);
  
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
  std::size_t missed = 0;
  for (int i = 0; i < 1000; i++) {
    x_dist = static_cast<double>(rand_x) + offset + gauss_dist(gen);
    y_dist = static_cast<double>(rand_y) + offset + gauss_dist(gen);
    std::cout << std::format("x_dist: {:>5.2f},  y_dist: {:>5.2f}\n", x_dist, y_dist );
    idx_x = static_cast<std::size_t>(std::floor(x_dist));
    idx_y = static_cast<std::size_t>(std::floor(y_dist));
    if (idx_x >= x_dim || idx_y >= y_dim) {
      missed++;
      continue;
    }
    pixel_matrix[idx_y][idx_x] = pixel_matrix[idx_y][idx_x] + 1;
  }
  
  printMatrix(pixel_matrix);
  std::cout << std::format("\nrand_x: {:>2d},  rand_y: {:>2d}\n", rand_x, rand_y);
  
  printMatrix(pixel_matrix, false, outfile);
  std::cout << std::format("\nmissed: {:>5d}\n", missed);

  outfile.close();

  return 0;
}
