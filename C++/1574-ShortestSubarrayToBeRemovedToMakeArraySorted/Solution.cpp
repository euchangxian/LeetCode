#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int findLengthOfShortestSubarray(std::vector<int>& arr) {
    // want: non-decreasing
    // input: any sequence of xi.
    // output: shortest subarray to remove from input.
    // since we can only remove one subarray, find the longest increasing
    // prefix, and the longest increasing suffix.
    // Then there are three choices: keep prefix => remove everything else,
    // keep suffix, or remove the entire subarray between the prefix and suffix?
    // Not entirely correct. Parts of the prefix/suffix may need to be removed
    // too. Specifically, find, for each prefix, the longest suffix that can be
    // kept. Keep the largest combination.
    // Not trivial to implement though...

    // find largest non-decreasing suffix,
    // i.e, x, y, z, 10, 11, 12
    //                ^r  points infront of z > 10, which breaks the
    //                monotonicity
    // check one "ahead", therefore r > 0 instead of r >= 0
    int r = static_cast<int>(arr.size()) - 1;
    while (r > 0 && arr[r - 1] <= arr[r]) {
      --r;
    }

    // Remove everything except the suffix.
    int result = r;

    // for each non-decreasing prefix,
    int l = 0;
    while (l < r && (l == 0 || arr[l - 1] <= arr[l])) {
      // check the suffix where we can continue the sequence.
      // remember that r would have been pointing to the "smallest" element
      // of the non-decreasing suffix.
      while (r < arr.size() && arr[l] > arr[r]) {
        ++r;
      }

      // try removing the middle subarray.
      // e.g.,
      // [1, 2, 3, 10, 4, 2, 3, 5]
      //        ^l=2         ^r=6
      // r is exclusive, therefore minus 1
      result = std::min(result, r - l - 1);
      ++l;
    }
    return result;
  }
};
