#include <array>
#include <bit>

constexpr std::array CANDIDATES = []() {
  std::array result = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
  for (auto& x : result) {
    --x;
  }
  return result;
}();

class Solution {
 public:
  int smallestNumber(int n) {
    // return smallest number x >= n, such that the binary repr of x only
    // contain set bits.
    // 2^n - 1
    // n <= 1000

    // Binary Search may be slower than Linear Search on such a small array,
    // possibly due to branch misprediction resulting in expensive pipeline
    // stalls.
    // return *std::ranges::lower_bound(CANDIDATES, n);

    // Linear Search
    // auto GTE = [n](int x) { return x >= n; };
    // return *std::ranges::find_if(CANDIDATES, GTE);

    return (1 << (32 - std::countl_zero(static_cast<unsigned int>(n)))) - 1;
  }
};
