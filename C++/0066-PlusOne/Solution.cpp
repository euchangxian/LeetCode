#include <vector>

class Solution {
 public:
  std::vector<int> plusOne(std::vector<int>& digits) {
    int n = digits.size();

    for (int i = n - 1; i >= 0; --i) {
      if (digits[i] < 9) {
        ++digits[i];
        return digits;
      }

      digits[i] = 0;
    }

    // This line will only be reached if all the original digits are 9
    std::vector<int> newDigits(n + 1, 0);
    newDigits[0] = 1;
    return newDigits;
  }
};
