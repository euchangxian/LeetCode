#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
class Solution {
private:
  random_device seed;
  mt19937 gen{seed()}; // seed the generator
  int randomInRange(int left, int right) {
    uniform_int_distribution<> dist{left, right};
    return dist(gen);
  }

  void quickSort(vector<int> &nums, int left, int right) {
    if (left >= right) {
      return; // sub-array is trivially sorted
    }

    int pivotIndex = randomInRange(left, right);

    // Bring the pivot to the front of the sub-array
    swap(nums[left], nums[pivotIndex]);

    auto [lt, gt] = partition(nums, left, right);

    quickSort(nums, left, lt - 1);
    quickSort(nums, gt + 1, right);
  }

  // Three Way Partition. Returns the index of the pivot after swapping all
  // nums[i] < pivot to the left of the pivot, all nums[i] > pivot to the right
  pair<int, int> partition(vector<int> &nums, int left, int right) {
    int pivot = nums[left];

    // lt represents the index to place a lower element
    int lt = left;

    // gt represents the index to place a higher element
    int gt = right;

    int i = left + 1; // scanning ptr
    while (i <= gt) {
      if (nums[i] < pivot) {
        swap(nums[i++], nums[lt++]);
      } else if (nums[i] == pivot) {
        ++i;
      } else {
        swap(nums[i], nums[gt--]);
      }
    }
    return {lt, gt};
  }

public:
  vector<int> sortArray(vector<int> &nums) {
    quickSort(nums, 0, nums.size() - 1);
    return nums;
  }
};
