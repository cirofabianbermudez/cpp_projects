#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int collatz(const int n) { return ((n % 2) * (2 * n + 1) + n) / 2; }

// To apply a function to each element of the vector
template <typename T, typename Func>
std::vector<double> vectTrans(const std::vector<T>& vec, Func func) {
  std::vector<double> result;
  result.reserve(vec.size());

  for (std::size_t i = 1; i < vec.size(); i++) {
    result.push_back(func((double)vec[i]));
  }
  return result;
}

template <typename T>
std::vector<T> cumsum(const std::vector<T>& vec) {
  std::vector<T> result;
  result.reserve(vec.size());

  result.push_back(vec[0]);
  for (std::size_t i = 1; i < vec.size(); i++) {
    result.push_back(vec[i] + result[i - 1]);
  }

  return result;
}

std::vector<double> rescale(const std::vector<double>& vec,
                            const double leftLimit, const double rightLimit) {
  std::vector<double> result;
  result.reserve(vec.size());

  auto min = std::min_element(vec.begin(), vec.end());
  auto max = std::max_element(vec.begin(), vec.end());

  double temp;
  for (std::size_t i = 0; i < vec.size(); i++) {
    temp = leftLimit +
           ((vec[i] - *min) / (*max - *min)) * (rightLimit - leftLimit);
    result.push_back(temp);
  }
  return result;
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

    auto mod = [](double x) { return std::fmod(x, 2.0); };
    auto cos = [](double x) { return std::cos(x); };
    auto sin = [](double x) { return std::sin(x); };

    t.reserve(sequence.size());
    x.reserve(sequence.size());
    y.reserve(sequence.size());

    t = cumsum(rescale(vectTrans(sequence, mod), ratioLeft, ratioRight));
    x = cumsum(vectTrans(t, cos));
    y = cumsum(vectTrans(t, sin));

    // Set fixed-point notation and precision
    std::cout << std::fixed << std::setprecision(5);
    for (std::size_t i = 0; i < x.size(); i++) {
      std::cout << std::setw(12) << std::setfill(' ') << x[i] << ", " << y[i]
                << std::endl;
    }
    std::cout << std::endl << std::endl;

    sequence.clear();
  }

  return 0;
}
