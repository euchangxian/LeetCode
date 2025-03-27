#include <vector>

class Solution {
 public:
  int minimumIndex(std::vector<int>& nums) {
    // nums is dominant if more than half the elements of nums have a value = x.
    // Given nums of length n with ONE dominannt element, split nums into
    // nums[..i] and nums[i+1..] such that
    // - both arrays are non-empty, and
    // - both have the same dominant element.
    // Return -1 if not possible.
    //
    // Hm. What properties make a split valid?
    // Considering the bare minimum, where the dominant value occurs (n+1)/2
    // times.
    // Then, consider the fraction a/n, where a = (n+1)/2
    // If sliding the partition index moves a dominant element from one to
    // the other, then we get: (a-1)/(n-1) and 1/1. Therefore, moving a dominant
    // element maintains the dominant property in both subarrays, where the
    // number of dominant element shifted must be greater than the
    // non-dominant elements.
    //
    // Oh lol. Noticed they didnt provide the dominant element. Need an O(N)
    // pass to figure out. Majority Element (Booyer-Moore's).
    // Then, another pass to figure out the prefix frequency of the dominant
    // element.
    // Then, final pass to determine a valid point.
    const int n = nums.size();
    int dominant = majority(nums);
    std::vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      prefix[i + 1] = prefix[i] + (nums[i] == dominant);
    }
    // for each split point
    // prefix = {0, 1, 2}
    for (int i = 0; i < n - 1; ++i) {
      bool left = prefix[i + 1] > (i + 1) / 2;
      bool right = prefix[n] - prefix[i + 1] > (n - i - 1) / 2;

      if (left && right) {
        return i;
      }
    }

    return -1;
  }

 private:
  int majority(const std::vector<int>& nums) {
    int majority;
    int count = 0;

    for (int num : nums) {
      if (count == 0) {
        majority = num;
      }

      count += (num == majority ? 1 : -1);
    }
    return majority;
  }
};
