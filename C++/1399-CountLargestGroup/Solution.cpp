#include <array>

constexpr int MAX_N = 1e4;
constexpr int MAX_SUM = 9 * 4;

constinit auto sumOfDigits = [](int n) {
  int sum = 0;
  while (n) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
};

constinit std::array<int, MAX_N + 1> maxSizedGroups = []() {
  std::array<int, MAX_N + 1> maxSizedGroups{};
  std::array<int, MAX_SUM + 1> groupSize{};

  int maxSize = 0;  // size of the largest group
  int count = 0;    // number of such groups
  for (int i = 1; i <= MAX_N; ++i) {
    int curr = ++groupSize[sumOfDigits(i)];
    if (curr > maxSize) {
      count = 1;
      maxSize = curr;
    } else if (curr == maxSize) {
      ++count;
    }

    maxSizedGroups[i] = count;
  }
  return maxSizedGroups;
}();

class Solution {
 public:
  int countLargestGroup(int n) {
    // Group [1..n] according to the sum of its digits.
    // Number of groups that have the largest size.
    // Since 1<=n<=10^4, the min sum is 1, max sum is sum(9999) = 36
    // compile-time fun i guess.
    return maxSizedGroups[n];
  }
};
