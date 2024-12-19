#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int maxChunksToSorted(std::vector<int>& arr) {
    // given permutation of intergers in the range [0..n-1]
    // partition arr and sort each partition. Concatenating the sorted chunks
    // together should return the sorted array {0, 1, ..., n-1}
    // Some form of monotonic property.
    // An already-sorted array can be splitted into n chunks, each of size 1.
    // Therefore, any decreasing subarrays can not be splitted. Only increasing
    // subarrays can.
    // NOTE: Not exactly right either. Notice that if the largest element is
    // at the front of the array, the entire array can only be splitted into
    // a single chunk, regardless of the suffix.
    // Hmmm. Monotonic stack doesnt seem simple. Seems to be something about
    // the relative positions of the max elements?
    //
    // Hm. Given that the elements are distinct in the range of [0..n-1],
    // notice that given a prefix subarray, all the elements within are
    // sortable if it is less than the expected max of that prefix.
    const std::size_t n = arr.size();

    int max = 0;
    int chunks = 0;
    for (int i = 0; i < n; ++i) {
      max = std::max(max, arr[i]);

      if (max <= i) {
        ++chunks;
      }
    }
    return chunks;
  }
};
