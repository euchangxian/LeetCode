#include <algorithm>
#include <cstdlib>
#include <random>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<int> sortArray(std::vector<int>& nums) {
    quickSort(nums, 0, nums.size() - 1);
    return nums;
  }

 private:
  std::random_device seed;
  std::mt19937 gen{seed()};  // seed the generator
  int randomInRange(int left, int right) {
    std::uniform_int_distribution<> dist{left, right};
    return dist(gen);
  }

  void quickSort(std::vector<int>& nums, int left, int right) {
    if (left >= right) {
      return;  // sub-array is trivially sorted
    }

    int pivotIndex = randomInRange(left, right);

    // Bring the pivot to the front of the sub-array
    std::swap(nums[left], nums[pivotIndex]);

    auto [lt, gt] = partition(nums, left, right);

    quickSort(nums, left, lt - 1);
    quickSort(nums, gt + 1, right);
  }

  // Three Way Partition. Returns the index of the pivot after swapping all
  // nums[i] < pivot to the left of the pivot, all nums[i] > pivot to the right
  std::pair<int, int> partition(std::vector<int>& nums, int left, int right) {
    int pivot = nums[left];

    // lt represents the index to place a lower element
    int lt = left;

    // gt represents the index to place a higher element
    int gt = right;

    int i = left + 1;  // scanning ptr
    while (i <= gt) {
      if (nums[i] < pivot) {
        std::swap(nums[i++], nums[lt++]);
      } else if (nums[i] == pivot) {
        ++i;
      } else {
        std::swap(nums[i], nums[gt--]);
      }
    }
    return {lt, gt};
  }
};
