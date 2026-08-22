class Solution {
 public:
  bool checkDivisibility(int n) {
    // determine whether n is divisible by the sum of:
    // - digit sum of n
    // - digit product of n
    auto sum = 0;
    auto prod = 1;

    auto k = n;
    while (k) {
      auto d = k % 10;
      k /= 10;
      sum += d;
      prod *= d;
    }
    return (n % (sum + prod)) == 0;
  }
};
