#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
  // nums is special iff there exists a number x such that there are exactly x
  // numbers in nums that are GTE to x. If nums is special, the value for x is
  // unique. x does not have to  be an element in nums.
  int specialArray(vector<int> &nums) {
    // binary search? x is upper bounded by nums.length
    // 1 <= nums.length <= 100, 0 <= nums[i] <= 1000
    // monotonic property here is the number of elements GTE to y decreases as y
    // increases.
    vector<int> freq = vector<int>(1001, 0);
    for (int i = 0; i < nums.size(); ++i) {
      ++freq[nums[i]];
    }

    int left = 0;
    int right = 101;
    while (left < right) {
      int x = left + (right - left) / 2;
      cout << x << "\n";

      // find the number of elements GTE to x
      int count = 0;
      for (int i = x; i < freq.size(); ++i) {
        count += freq[i];
      }

      if (count == x) {
        return x;
      }

      // update bounds
      if (count < x) {
        right = x;
      } else {
        left = x + 1;
      }
    }
    return -1;
  }
};

int main(int argc, char *argv[]) {
  vector<int> nums = {3, 5};
  cout << Solution().specialArray(nums) << endl; // expect 2

  nums = {0, 0};
  cout << Solution().specialArray(nums) << endl; // expect -1

  nums = {0, 4, 3, 0, 4};
  cout << Solution().specialArray(nums) << endl; // expect 3

  nums = {3, 6, 7, 7, 0};
  cout << Solution().specialArray(nums) << endl;

  nums = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
          100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
          100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
          100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
          100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
          100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
          100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
          100, 100, 100, 100, 100, 100, 100, 100, 100};
  cout << Solution().specialArray(nums) << endl; // expect 100
}
