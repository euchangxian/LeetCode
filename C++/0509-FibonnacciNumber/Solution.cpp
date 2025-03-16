#include <array>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <utility>

template <typename T, int N>
class Matrix {
 public:
  std::array<std::array<T, N>, N> data{};

  Matrix() = default;

  Matrix(const std::array<std::array<T, N>, N>& initial) : data(initial) {}

  std::array<T, N>& operator[](int index) { return data[index]; }

  const std::array<T, N>& operator[](int index) const { return data[index]; }

  Matrix operator*(const Matrix& other) const {
    Matrix result;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        result.data[i][j] = 0;
        for (int k = 0; k < N; ++k) {
          result.data[i][j] += data[i][k] * other.data[k][j];
        }
      }
    }
    return result;
  }

  Matrix operator*=(const Matrix& other) {
    *this = *this * other;
    return *this;
  }

  std::array<T, N> operator*(const std::array<T, N>& vec) const {
    std::array<T, N> result{};
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        result[i] += data[i][j] * vec[j];
      }
    }
    return result;
  }

  Matrix operator^(long long exponent) const {
    assert(exponent >= 0);
    Matrix result;
    // Initialize result as identity matrix
    for (int i = 0; i < N; ++i) {
      result.data[i][i] = 1;
    }

    Matrix base(*this);
    while (exponent > 0) {
      if (exponent & 1) {
        result = result * base;
      }
      base = base * base;
      exponent >>= 1;
    }
    return result;
  }

  Matrix& operator^=(long long exponent) {
    *this = *this ^ exponent;
    return *this;
  }

  static Matrix identity() {
    Matrix result;
    for (int i = 0; i < N; ++i) {
      result.data[i][i] = 1;
    }
    return result;
  }
};

class Solution {
 public:
  int fib(int n) {
    if (n <= 1) {
      return n;
    }

    Matrix<int, 2> base{{{
        {1, 1},
        {1, 0},
    }}};
    base ^= (n - 1);
    return base[0][0];
  }

  int fibIter(int n) {
    if (n <= 1) {
      return n;
    }

    int a = 0;
    int b = 1;
    for (int i = 2; i <= n; ++i) {
      a = std::exchange(b, a + b);
    }
    return b;
  }
};
