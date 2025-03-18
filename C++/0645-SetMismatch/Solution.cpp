#include <cstddef>
#include <vector>

class Solution {
 public:
  std::vector<int> findErrorNums(std::vector<int>& nums) {
    // Find the numbers that occur twice and the number that is missing.
    // XOR and sum (since 1 to n)
    // XOR with [1..n] and nums[i]. This ensures that every number that
    // appears once will be XOR-ed a total of two times, effectively resulting
    // in 0, whereas the number that appears twice will be XOR-ed three times.
    // However, the missing number will be XOR-ed once.
    // Thus, another approach is necessary.
    // This requires exploiting the property that the numbers lie in the
    // range [1..n].
    // Thus, by modifying the array in-place, the duplicate number can be
    // figured out.
    const int n = nums.size();

    int duplicateNumber = 0;
    int missingNumber = (n * (n + 1)) / 2;

    for (int i = 0; i < n; ++i) {
      // num is 1-indexed
      const int num = abs(nums[i]);

      if (nums[num - 1] < 0) {
        // A previous iteration already flipped this position
        duplicateNumber = num;
      }

      // Flip the number pointed to by num
      nums[num - 1] *= -1;

      missingNumber -= num;
    }

    return {duplicateNumber, missingNumber + duplicateNumber};
  }
};
