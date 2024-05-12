#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int collatz(const int n) { return ((n % 2) * (2 * n + 1) + n) / 2; }

std::vector<double> mod(const std::vector<int>& array, const double arg) {
  std::vector<double> res_vect = {};
  double temp;
  for (std::size_t i = 1; i < array.size(); i++) {
    temp = std::fmod((double)array[i], arg);
    res_vect.push_back(temp);
  }
  return res_vect;
}

template <typename T>
std::vector<T> cumsum(const std::vector<T>& array) {
  std::vector<T> temp = array;
  for (std::size_t i = 1; i < array.size(); i++) {
    temp[i] = temp[i] + temp[i - 1];
  }
  return temp;
}

std::vector<double> rescale(const std::vector<double>& array,
                            const double leftLimit, const double rightLimit) {
  std::vector<double> res_vect;
  auto min = std::min_element(array.begin(), array.end());
  auto max = std::max_element(array.begin(), array.end());
  double temp;
  for (std::size_t i = 0; i < array.size(); i++) {
    temp = leftLimit + (((double)array[i] - *min) / (*max - *min)) *
                           (rightLimit - leftLimit);
    res_vect.push_back(temp);
  }
  return res_vect;
}

template <typename T>
void print_vector(const std::vector<T>& array,
                  const std::string& message = "array") {
  for (std::size_t i = 0; i < array.size(); i++) {
    std::cout << message << "[" << i << "] = " << array[i] << std::endl;
  }
}

int main(int argc, char** argv) {
  const int distLeft = 1;
  const int distRight = 1e6;
  const int distElements = 1000;

  const double ratioLeft = -0.09;
  const double ratioRight = 0.08;

  std::random_device rd;   // Seed
  std::mt19937 rng(rd());  // Seed engine
  std::uniform_int_distribution<int> distrib(distLeft, distRight);

  std::vector<int> sequence;
  std::vector<double> t, x, y;

  for (int i = 0; i < distElements; i++) {
    sequence.push_back(distrib(rng));

    while (sequence.back() > 1) {
      sequence.push_back(collatz(sequence.back()));
    }

    std::reverse(sequence.begin(), sequence.end());

    t = cumsum(rescale(mod(sequence, 2.0), ratioLeft, ratioRight));

    x.resize(t.size());
    y.resize(t.size());

    // std::transform(t.begin(), t.end(), std::back_inserter(x), [](double t) {
    // return std::cos(t); });
    std::transform(t.begin(), t.end(), x.begin(),
                   [](double t) { return std::cos(t); });
    x = cumsum(x);

    // std::transform(t.begin(), t.end(), std::back_inserter(y), [](double t) {
    // return std::sin(t); });
    std::transform(t.begin(), t.end(), y.begin(),
                   [](double t) { return std::sin(t); });
    y = cumsum(y);

    // print_vector(x, "x");
    // print_vector(y, "y");

    // Set fixed-point notation and precision
    std::cout << std::fixed << std::setprecision(5);
    for (std::size_t i = 0; i < x.size(); i++) {
      std::cout << std::setw(12) << std::setfill(' ') << x[i] << ", " << y[i]
                << std::endl;
    }
    std::cout << std::endl << std::endl;

    sequence.clear();
    // t.clear();
    // x.clear();
    // y.clear();
  }

  return 0;
}
