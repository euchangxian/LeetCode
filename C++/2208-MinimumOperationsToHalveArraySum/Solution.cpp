#include <algorithm>
#include <cstddef>
#include <vector>

class Solution {
 public:
  int halveArray(std::vector<int>& nums) {
    const size_t n = nums.size();

    double sum = 0;
    std::vector<double> dblNums(n);
    for (size_t i = 0; i < n; ++i) {
      dblNums[i] = static_cast<double>(nums[i]);
      sum += dblNums[i];
    }
    // Avoid casting. Ceiling Division.
    double target = sum / 2;

    std::make_heap(dblNums.begin(), dblNums.end());

    int operations = 0;
    // Greedily pick the largest num and halve it.
    while (target > 0) {
      const double halved = dblNums.front() / 2;
      std::pop_heap(dblNums.begin(), dblNums.end());

      target -= halved;

      dblNums.back() = halved;
      std::push_heap(dblNums.begin(), dblNums.end());
      ++operations;
    }
    return operations;
  }
};
