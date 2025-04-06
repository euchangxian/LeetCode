#include <unordered_set>
#include <utility>
#include <vector>

class Solution {
 public:
  int subarrayBitwiseORs(std::vector<int>& nums) {
    const int n = nums.size();

    std::unordered_set<int> unique{nums[0]};
    for (int i = 1; i < n; ++i) {
      int prevOR = 0;
      int currOR = nums[i];
      unique.insert(currOR);

      // Runs at most 30 times for each differing BIT, adding a potentially
      // new subarray into the answer.
      for (int j = i - 1; j >= 0 && currOR != prevOR; --j) {
        prevOR |= nums[j];
        currOR |= nums[j];
        unique.insert(currOR);
      }
    }

    return unique.size();
  }

  int subarrayBitwiseORsNaive(std::vector<int>& nums) {
    // Distinct bitwise ORs of all the non-empty subarrays of nums.
    // Subarrays: Contiguous
    // OR: OR-Sum is monotonically non-decreasing.
    //
    // Definitely not a naive Sliding Window solution, given that we cant
    // inverse an OR operation.
    //
    // First, consider a simpler version: unique elements only.
    // This means nums[i] must differ from every other nums[j] in at least one
    // bit position.
    // Then, the number of different possible OR-sums is thus n + n-1 + ... + 1
    // which is n(n+1)/2
    //
    // Extending this to non-distinct: Count unique elements?
    // Ah. This fails for the trivial case {3, 11}, returning 3,
    // where the distinct subarrays are {3}, {11} (3 | 11 == 11).
    // This happens when an element is a subset of another in terms of set bits,
    // causing their OR-sum to not be distinct.
    const int n = nums.size();

    std::unordered_set<int> ans;

    // all unique subarray sums
    std::unordered_set<int> prev;
    for (int x : nums) {
      std::unordered_set<int> curr{x};
      for (int sum : prev) {
        curr.insert(x | sum);
      }

      ans.insert(curr.begin(), curr.end());
      prev = std::move(curr);
    }
    return ans.size();
  }
};
