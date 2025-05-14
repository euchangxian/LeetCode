#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
constexpr int MOD = 1E9 + 7;

template <typename T, int N>
class Matrix {
 public:
  std::array<std::array<T, N>, N> data{};

  Matrix() = default;

  Matrix(const std::array<std::array<T, N>, N>& initial) : data(initial) {}

  Matrix(std::array<std::array<T, N>, N>&& initial)
      : data(std::move(initial)) {}

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

#include <iostream>
#include <istream>
#include <type_traits>

template <typename T = int, int MOD = 1'000'000'007>
class ModNum {
  template <typename U = T>
  using safe_multiply_t =
      std::conditional_t<std::is_same_v<U, int>, long long, U>;

 public:
  ModNum() : x(0) {}

  template <typename U>
  ModNum(U v) {
    if constexpr (std::is_same_v<T, int>) {
      x = static_cast<T>(static_cast<long long>(v) % MOD);
    } else {
      x = static_cast<T>(v % MOD);
    }

    if (x < 0) {
      x += MOD;
    }
  }

  constexpr T get() const noexcept { return x; }
  constexpr operator int() const noexcept { return static_cast<int>(x); }
  constexpr operator long long() const noexcept {
    return static_cast<long long>(x);
  }

  // ModNum + ModNum
  ModNum<T, MOD> operator+(const ModNum<T, MOD>& other) const {
    ModNum<T, MOD> result(*this);
    result += other;
    return result;
  }

  // ModNum + arithmetic type
  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD> operator+(U other) const {
    if constexpr (std::is_same_v<T, int>) {
      return ModNum<T, MOD>(
          static_cast<T>((static_cast<long long>(x) + other) % MOD));
    }
    return ModNum<T, MOD>(static_cast<T>((x + other) % MOD));
  }

  ModNum<T, MOD>& operator+=(const ModNum& other) {
    x += other.x;
    if (x >= MOD) {
      x -= MOD;
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD>& operator+=(U other) {
    ModNum<T, MOD> temp(other);
    return *this += temp;
  }

  // WARNING: shifts the number into the positive range. Not remainder.
  ModNum<T, MOD> operator-(const ModNum<T, MOD>& other) const {
    ModNum<T, MOD> result(*this);
    result -= other;
    return result;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD> operator-(U other) const {
    ModNum<T, MOD> temp(other);
    return *this -= temp;
  }

  ModNum<T, MOD>& operator-=(const ModNum<T, MOD>& other) {
    if (x < other.x) {
      x += MOD;
    }
    x -= other.x;
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD>& operator-=(U other) {
    ModNum<T, MOD> temp(other);
    return *this -= temp;
  }

  ModNum<T, MOD> operator*(const ModNum<T, MOD>& other) const {
    ModNum<T, MOD> result(*this);
    result *= other;
    return result;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD> operator*(U other) const {
    ModNum<T, MOD> result(*this);
    result *= other;
    return result;
  }

  ModNum<T, MOD>& operator*=(const ModNum<T, MOD>& other) {
    x = static_cast<T>((static_cast<safe_multiply_t<T>>(x) * other.x) % MOD);
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD>& operator*=(U other) {
    ModNum<T, MOD> temp(other);
    return *this *= temp;
  }

  // Division (using Fermat's little theorem for modular inverse)
  ModNum<T, MOD> inverse() const { return modPow(MOD - 2); }

  ModNum<T, MOD> operator/(const ModNum<T, MOD>& other) const {
    ModNum<T, MOD> result(*this);
    result /= other;
    return result;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD> operator/(U other) const {
    ModNum<T, MOD> result(*this);
    result /= other;
    return result;
  }

  ModNum<T, MOD>& operator/=(const ModNum<T, MOD>& other) {
    return *this *= other.inverse();
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD>& operator/=(U other) {
    return *this /= ModNum<T, MOD>(other);
  }

  // Power (using binary exponentiation)
  ModNum<T, MOD> modPow(T exponent) const {
    ModNum<T, MOD> result(1);
    ModNum<T, MOD> base(*this);

    while (exponent > 0) {
      if (exponent & 1) {
        result *= base;
      }
      base *= base;
      exponent >>= 1;
    }

    return result;
  }

  bool operator==(const ModNum<T, MOD>& other) const { return x == other.x; }
  bool operator!=(const ModNum<T, MOD>& other) const { return x != other.x; }

  friend std::ostream& operator<<(std::ostream& os, const ModNum<T, MOD>& num) {
    return os << num.x;
  }

  friend std::istream& operator>>(std::istream& is, ModNum<T, MOD>& num) {
    T v;
    is >> v;
    num = ModNum<T, MOD>(v);
    return is;
  }

  // Non-member friend operators for arithmetic + ModNun
  template <typename U>
  friend typename std::enable_if_t<std::is_arithmetic_v<U>, ModNum<T, MOD>>
  operator+(U a, const ModNum<T, MOD>& b) {
    return ModNum<T, MOD>(a) + b;
  }

  template <typename U>
  friend typename std::enable_if_t<std::is_arithmetic_v<U>, ModNum<T, MOD>>
  operator-(U a, const ModNum<T, MOD>& b) {
    return ModNum<T, MOD>(a) - b;
  }

  template <typename U>
  friend typename std::enable_if_t<std::is_arithmetic_v<U>, ModNum<T, MOD>>
  operator*(U a, const ModNum<T, MOD>& b) {
    return ModNum<T, MOD>(a) * b;
  }

  template <typename U>
  friend typename std::enable_if_t<std::is_arithmetic_v<U>, ModNum<T, MOD>>
  operator/(U a, const ModNum<T, MOD>& b) {
    return ModNum<T, MOD>(a) / b;
  }

 private:
  T x;
};

class Solution {
 public:
  int lengthAfterTransformations(std::string_view s,
                                 int t,
                                 std::vector<int>& nums) {
    // Perform t transformations.
    // In one transformation, replace every character in s:
    // - s[i] becomes the next nums[s[i]-'a'] characters.
    //   e.g., if nums[0]=3, 'a' becomes "bcd"
    // - The transformation wraps around.
    //
    // t <= 1E9
    // 1 <= nums[i] <= 25
    //
    // s = "ab", nums = {2, 2} -> "bccd"
    // 1 1 0 0  * 0 1 1 0  = 0 1 2 1
    // 0 0 0 0    0 0 1 1    0 0 0 0
    Matrix<ModNum<int>, 26> shift{};
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < nums[i]; ++j) {
        shift[i][(i + 1 + j) % 26] += 1;
      }
    }

    Matrix<ModNum<int>, 26> freq{};
    for (char c : s) {
      freq[0][c - 'a'] += 1;
    }

    shift ^= t;
    freq *= shift;

    ModNum<int> result = 0;
    for (int i = 0; i < 26; ++i) {
      result += freq[0][i];
    }
    return result.get();
  }
};
