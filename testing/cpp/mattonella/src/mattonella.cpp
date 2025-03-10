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

// =============================== FUNCTIONS ================================ //

template<typename T>
void printMatrix(const std::vector<std::vector<T>>& matrix, bool invertRows = true, std::ostream& out = std::cout) {
  double value = 0.0;

  // matrix[rows][columns]
  // matrix[  i ][  j  ]
  // matrix[  y ][  x  ]
  
  std::size_t Rows = matrix.size();
  std::size_t Cols = !matrix.empty()? matrix[0].size() : 0;

  out << "\n";
  
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

template<typename T>
void printMatrixUVC(const std::vector<std::vector<T>>& matrix, int offset_ps = 3000, std::ostream& out = std::cout) {
  int value = 0;

  // matrix[rows][columns]
  // matrix[  i ][  j  ]
  // matrix[  y ][  x  ]
  
  std::size_t Rows = matrix.size();
  std::size_t Cols = !matrix.empty()? matrix[0].size() : 0;

  // Print rows in normal order (top to bottom)
  for (std::size_t i = 0; i < Rows; ++i) {
    for (std::size_t j = 0; j < Cols; ++j) {
      value = static_cast<int>( matrix[i][j] );
      out << std::format("{:>4d} {:>4d} {:>8d} {:>8d}\n", i, j, value, offset_ps);
    }
  }
}

// ================================== MAIN ================================== //

int main(int argc, char* argv[]) {
  
  // Parse command line arguments
  if (argc < 3) {
    std::cerr << "Error:\n Usage: " << argv[0] << " <x_dim> <y_dim>\n";
    return 1;
  }

  // Pixel matrix dimensions 
  int x_dim = 0;
  int y_dim = 0;
  
  // Parse input arguments
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
  
  std::cout << std::format("\n[INFO]: x_dim: {:>5d},  y_dim: {:>5d}\n", x_dim, y_dim);

  // Define output file
  std::string filename = "../../data/mattonella.txt";
  std::ofstream outfile;
  outfile.open(filename);

  std::string filename1 = "../../data/uvc_mattonella.txt";
  std::ofstream uvcfile;
  uvcfile.open(filename1);

  // Random number generator setup
  std::random_device rd;      // Non-deterministic source (seed)
  std::mt19937 gen(rd());     // Seed the generator

  // Create mattonella matrix
  std::vector<std::vector<double>> pixel_matrix(y_dim, std::vector<double>(x_dim, 0.0));
  
  // Define a uniform distribution
  //std::uniform_real_distribution<> dist(0.0, 1.0);
  //std::uniform_int_distribution<> dist(0, 1);
  std::uniform_int_distribution<> uniform_dist(4, 5);
  std::uniform_int_distribution<> uniform_dist_charge(10, 32000);
  
  // Define the Gaussian distribution mean = 0.0, std = 1.0
  std::normal_distribution gauss_dist(0.0, 0.8);
  //std::normal_distribution gauss2(0.0, 1.0);
 
  // Generate random hit
  int rand_x = uniform_dist(gen);
  int rand_y = uniform_dist(gen);
  int charge = uniform_dist_charge(gen);
  
  std::cout << std::format("[INFO]: rand_x: {:>4d},  rand_y: {:>4d}, charge: {:>4d}\n", rand_x, rand_y, charge);

  // Generate random numbers to spread
  double x_dist;
  double y_dist;
  double offset = 0.5;
  int iter = 10000;
  
  // Indexes
  int idx_x = 0;
  int idx_y = 0;
  int missed = 0;

  // Fill buckets
  for (int i = 0; i < iter; i++) {
    x_dist = static_cast<double>(rand_x) + offset + gauss_dist(gen);
    y_dist = static_cast<double>(rand_y) + offset + gauss_dist(gen);
    //std::cout << std::format("x_dist: {:>5.2f},  y_dist: {:>5.2f}\n", x_dist, y_dist );
    idx_x = std::floor(x_dist);
    idx_y = std::floor(y_dist);
    if (idx_x >= x_dim || idx_y >= y_dim || idx_x < 0 || idx_y < 0) {
      //std::cout << std::format("[INFO]: iter {:>4d}, x: {:>4d},  y: {:>4d} MISSED\n", i, idx_x, idx_y);
      missed++;
      continue;
    } else {
      //std::cout << std::format("[INFO]: iter {:>4d}, x: {:>4d},  y: {:>4d}\n", i, idx_x, idx_y);
    }
    pixel_matrix[idx_y][idx_x] = pixel_matrix[idx_y][idx_x] + 1;
  }

  // Print matrix pre-normalization
  std::cout << std::format("\n[INFO]: missed: {:>5d}\n", missed);
  printMatrix(pixel_matrix);
  
  for (int y = 0; y < y_dim; ++y) {
    for (int x = 0; x < x_dim; ++x) {
      pixel_matrix[y][x] = ( pixel_matrix[y][x] / (iter - missed) ) * static_cast<double>(charge);
    }
  }
  
  // Print matrix to console and file
  printMatrix(pixel_matrix);
  printMatrix(pixel_matrix, false, outfile);

  // Print matrix for UVC
  printMatrixUVC(pixel_matrix, 3000, uvcfile);

  // Close files
  outfile.close();
  uvcfile.close();

  return 0;
}
