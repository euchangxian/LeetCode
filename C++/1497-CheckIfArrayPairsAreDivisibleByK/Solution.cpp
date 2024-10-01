#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

constexpr size_t kBuckets{100000}; // 10^5

using namespace std;
class Solution {
public:
  bool canArrange(vector<int> &arr, int k) {
    // Sort and two pointer? Can we do better than O(nlogn)?
    // Sorting does not work. CounterExample: {1, 4, 5, 10,} => {1, 10}, {4, 5}
    // But there exists a valid pairing {1, 4}, {5, 10}.
    // What about grouping by buckets where there are K buckets.
    // i.e., the above example would be {5, 10}, {1}, {}, {}, {4}
    // remainder 0 paired with their selves.
    // remainder 1 will be paired with remainder k-1
    // and so on..
    // For pairing, no need to iterate through. Just have to check that the
    // number of elements in the buckets are equal (or divisible by 2 for zero)
    std::array<int32_t, kBuckets> buckets{};

    for (const int &num : arr) {
      const size_t idx = ((num % k) + k) % k; // Ensure positive index
      ++buckets[idx];
    }

    if (buckets[0] % 2) {
      // Non-even amount of elements in the 0-th bucket.
      return false;
    }

    size_t l{1};
    size_t r{static_cast<size_t>(k) - 1};
    while (l < r) {
      if (buckets[l] != buckets[r]) {
        return false;
      }
      ++l;
      --r;
    }

    return true;
  }
};
