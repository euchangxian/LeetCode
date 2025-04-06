#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<int> findClosestElements(std::vector<int>& nums, int k, int x) {
    // Given sorted nums, find the k-closest elements to x.
    // Naively, transform nums into A, A[i] = {abs(nums[i] - x), nums[i]};
    // Then, sort and take the k smallest difference.
    //
    // But thats not exploiting the sorted order.
    // Notice that we can somewhat do a fixed-sized sliding window of size k.
    // We first do std::lower_bound to find the closest element to x.
    //
    // Intuitively, we can do a Binary Search on our Start point of the
    // subarray.
    const int n = nums.size();

    auto it = std::lower_bound(nums.begin(), nums.end(), x);
    int l = (it - 1) - nums.begin();
    int r = it - nums.begin();

    // decrement/increment k times
    int elems = 0;
    while (l >= 0 && r < n && elems < k) {
      // prefer lexicographically smaller.
      if (x - nums[l] <= nums[r] - x) {
        --l;
      } else {
        ++r;
      }
      ++elems;
    }

    if (elems < k && l >= 0) {
      l -= (k - elems);
    }

    if (elems < k && r < n) {
      r += (k - elems);
    }

    std::vector<int> ans;
    ans.reserve(k);
    // r-l == k
    for (int i = l + 1; i < r; ++i) {
      ans.push_back(nums[i]);
    }
    return ans;
  }
};
