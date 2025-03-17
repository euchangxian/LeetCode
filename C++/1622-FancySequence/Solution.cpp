#include <iostream>
#include <istream>
#include <type_traits>
#include <vector>

template <typename T = int, int MOD = 1'000'000'007>
class ModNum {
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

  T get() const { return x; }
  operator int() const { return static_cast<int>(x); }
  operator long long() const { return static_cast<long long>(x); }

  // ModNum + ModNum
  ModNum<T, MOD> operator+(const ModNum<T, MOD>& other) const {
    if constexpr (std::is_same_v<T, int>) {
      return ModNum<T, MOD>(
          static_cast<T>((static_cast<long long>(x) + other.x) % MOD));
    }
    return ModNum<T, MOD>(static_cast<T>((x + other.x) % MOD));
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
    if constexpr (std::is_same_v<T, int>) {
      x = static_cast<T>((static_cast<long long>(x) + other.x) % MOD);
    } else {
      x = static_cast<T>((x + other.x) % MOD);
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD>& operator+=(U other) {
    if constexpr (std::is_same_v<T, int>) {
      x = static_cast<T>((static_cast<long long>(x) + other) % MOD);
    } else {
      x = static_cast<T>((x + other) % MOD);
    }
    return *this;
  }

  // WARNING: shifts the number into the positive range. Not remainder.
  ModNum<T, MOD> operator-(const ModNum<T, MOD>& other) const {
    if constexpr (std::is_same_v<T, int>) {
      return ModNum<T, MOD>(
          static_cast<T>((static_cast<long long>(x) - other.x + MOD) % MOD));
    }
    return ModNum<T, MOD>(static_cast<T>((x - other.x + MOD) % MOD));
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD> operator-(U other) const {
    if constexpr (std::is_same_v<T, int>) {
      return ModNum<T, MOD>(
          static_cast<T>((static_cast<long long>(x) - other + MOD) % MOD));
    }
    return ModNum<T, MOD>(static_cast<T>((x - other + MOD) % MOD));
  }

  ModNum<T, MOD>& operator-=(const ModNum<T, MOD>& other) {
    if constexpr (std::is_same_v<T, int>) {
      x = static_cast<T>((static_cast<long long>(x) - other.x + MOD) % MOD);
    } else {
      x = static_cast<T>((x - other.x + MOD) % MOD);
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD>& operator-=(U other) {
    if constexpr (std::is_same_v<T, int>) {
      x = static_cast<T>((static_cast<long long>(x) - other + MOD) % MOD);
    } else {
      x = static_cast<T>((x - other + MOD) % MOD);
    }
    return *this;
  }

  ModNum<T, MOD> operator*(const ModNum<T, MOD>& other) const {
    if constexpr (std::is_same_v<T, int>) {
      return ModNum<T, MOD>(
          static_cast<T>((static_cast<long long>(x) * other.x) % MOD));
    }
    return ModNum<T, MOD>(static_cast<T>((x * other.x) % MOD));
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD> operator*(U other) const {
    if constexpr (std::is_same_v<T, int>) {
      return ModNum<T, MOD>(
          static_cast<T>((static_cast<long long>(x) * other) % MOD));
    }
    return ModNum<T, MOD>(static_cast<T>((x * other) % MOD));
  }

  ModNum<T, MOD>& operator*=(const ModNum<T, MOD>& other) {
    if constexpr (std::is_same_v<T, int>) {
      x = static_cast<T>((static_cast<long long>(x) * other.x) % MOD);
    } else {
      x = static_cast<T>((x * other.x) % MOD);
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD>& operator*=(U other) {
    if constexpr (std::is_same_v<T, int>) {
      x = static_cast<T>((static_cast<long long>(x) * other) % MOD);
    } else {
      x = static_cast<T>((x * other) % MOD);
    }
    return *this;
  }

  // Division (using Fermat's little theorem for modular inverse)
  ModNum<T, MOD> inverse() const { return modPow(MOD - 2); }

  ModNum<T, MOD> operator/(const ModNum<T, MOD>& other) const {
    return *this * other.inverse();
  }

  template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<U>>>
  ModNum<T, MOD> operator/(U other) const {
    return *this / ModNum<T, MOD>(other);
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
    ModNum<T, MOD> base(x);

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

constexpr int MOD{1'000'000'007};
// MATH.
// A[i] * totalMult + totalIncr
//
// addAll(incr): totalIncr += incr
//
// For multAll(m), slightly more complicated. Suppose our current value is
// A[i] * totalMult + totalIncr. Then, multiplying by m:
// ((A[i] * totalMult) + totalIncr) * m == A[i] * (totalMult*m) + (totalIncr*m)
// Concisely:
// totalMult *= m
// totalIncr *= m
// Note that we can use modMult, modIncr for both of these operations, since
// (a + b) % m == ((a%m) + (b%m)) % m
// (a * b) % m == ((a%m) * (b%m)) % m
//
// For append(val), given that the existing multiplier and increment will not
// be able to apply to the new val trivially, the next conclusion would be to
// eagerly update the new value first such that:
// newVal * totalMult + totalIncr == val
// This means we need to do:
// (val - totalIncr) / totalMult == newVal
// For modMinus, the equation:
// (a - b) % m == ((a%m) - (b%m)) % m
// still holds.
//
// But for modDiv,
// (a / b) % m == ((a%m) / (b%m)) % m
// does NOT hold.
// Instead, modInverse is necessary.
// Since mod=10e9 + 7 is a prime, Fermat's Little Theorem holds.
class Fancy {
 public:
  Fancy() : mult(1), incr(0) { nums.reserve(N); }

  void append(int val) {
    int newVal = (val - incr) / mult;
    nums.push_back(newVal);
  }

  void addAll(int inc) { incr += inc; }

  void multAll(int m) {
    mult *= m;
    incr *= m;
  }

  int getIndex(int idx) {
    if (idx >= nums.size()) {
      return -1;
    }
    return nums[idx] * mult + incr;
  }

 private:
  static constexpr int N{100'001};
  std::vector<int> nums;

  ModNum<int, MOD> mult;
  ModNum<int, MOD> incr;
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
