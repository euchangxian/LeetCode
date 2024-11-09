#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

using namespace std;
class Solution {
 public:
  bool canMakeArithmeticProgression(vector<int>& arr) {
    // an array is an AP if the difference between any two consecutive elements
    // are the same.
    // Most straightforward way: Sort in ascending, check difference. O(nlogn)
    // Can we do better?
    //
    // Yeah.... Find the min/max element. This will let us deduce the arithmetic
    // progression. I.e., the difference between any two consecutive element,
    // diff = (max - min) / (arr.size - 1)
    //
    // Then, we must have n-2 (excluding the min and max) distinct values
    // where each of these values are min + (k * diff), i.e., some multiple of
    // diff.
    // This can be done using a Set. O(n) space/time.
    //
    // Optimizing further, we can perform this in-place. Since our elements can
    // already be deduced using min + (k * diff), k actually represents the
    // index in the array where the element should be.
    // Therefore, iterating through the array, when we encounter an element,
    // we can deduce the index the element should belong to, and swap it with
    // the element currently at that index. If the element to-be-swapped is
    // already in its correct position, then we know that this sequence of
    // values do not contain the correct elements.
    // Also known as cyclic sorting.
    auto [minIt, maxIt] = std::minmax_element(arr.begin(), arr.end());

    // WARNING: any kind of modifications to the array would result in undefined
    // behavior when dereferencing the iterators....
    int min = *minIt;
    int max = *maxIt;
    if ((max - min) % (arr.size() - 1)) {
      // if there is a remainder
      return false;
    }

    // Deduce the expected difference between consecutive elements of the AP
    int diff = (max - min) / (arr.size() - 1);

    // Handle edge case where diff = 0 => all elements must be equal.
    if (diff == 0) {
      return std::all_of(arr.begin(), arr.end(),
                         [min](int num) { return num == min; });
    }

    int i = 0;
    while (i < arr.size()) {
      if ((arr[i] - min) % diff) {
        // if not divisible by diff, then just return early
        return false;
      }

      // The expected index.
      int k = (arr[i] - min) / diff;
      if (k == i) {
        ++i;  // the only branch that increments i
        continue;
      }

      // Check the element at that index. If not divisible by diff, or
      // already in its correct position, then return false early.
      if ((arr[k] - min) % diff || k == (arr[k] - min) / diff) {
        return false;
      }

      // otherwise, swap, then check this position in the next iteration.
      std::swap(arr[i], arr[k]);
    }

    return true;
  }
};
