#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  long long maxKelements(vector<int>& nums, int k) {
    // Greedily choose the maximum element in each iteration? Top k elements?
    // Simulation works I guess.
    std::make_heap(nums.begin(), nums.end());

    long long score = 0LL;
    for (size_t i = 0; i < k; ++i) {
      const int num = nums.front();
      std::pop_heap(nums.begin(), nums.end());
      // Instead of actually popping and potentially causing a reallocation,
      // make use of the pop_heap moving the top element to the back of the
      // array.
      // nums.pop_back();

      score += num;

      const int afterOp = std::ceil(static_cast<double>(num) / 3.0);

      // Similarly, instead of actually pushing which could potentially cause
      // reallocations, simply replace the back element which will be the
      // 'popped' element after invoking std::pop_heap.
      // nums.push_back(afterOp);
      nums.back() = afterOp;
      std::push_heap(nums.begin(), nums.end());
    }

    return score;
  }
};
