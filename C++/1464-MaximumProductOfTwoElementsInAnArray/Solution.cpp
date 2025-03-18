#include <algorithm>
#include <climits>
#include <cstddef>
#include <vector>

class Solution {
 public:
  int maxProduct(std::vector<int>& nums) {
    // Lol. Get max, get second max. Single pass
    int largest = INT_MIN;
    int secondLargest = INT_MIN;

    for (const int num : nums) {
      if (num > largest) {
        secondLargest = largest;
        largest = num;
      } else if (num > secondLargest) {
        secondLargest = num;
      }
    }
    return (largest - 1) * (secondLargest - 1);
  }
};
