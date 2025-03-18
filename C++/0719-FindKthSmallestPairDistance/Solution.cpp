#include <algorithm>
#include <vector>

class Solution {
 public:
  int smallestDistancePair(std::vector<int>& nums, int k) {
    // Notice that we only need the kth smallest distance, not the actual
    // pairs that produce the distance. This allows us to perform lots of
    // optimizations.
    //
    // First of all, notice that the range of distances is finite and bounded.
    // The smallest distance will be the distance between the first and
    // second smallest element. 0 can be used for simplicity.
    // The largest distance will be the distance between the
    // largest and smallest element.
    // The difficulty is determining which of these distances is the kth
    // smallest.
    //
    // To do this, keep the range of distances in mind.
    // A little logical leap (at least for me) is to realize that as the
    // distance d increases, the number of pairs that have distance LTE
    // to d increases.
    // As such, we can do a binary search on the range of distance using
    // this monotonic property, where we look for the smallest distance d
    // such that there are at least k pairs with distance <= d.
    //
    // Next is how to count pairs that have distance <= d efficiently.
    // The largest distance is always between the smallest element and the
    // largest element.
    // By sorting the array, the largest distance of any subarray can be
    // efficiently computed.
    //
    // This means that for any distance d, if the largest distance of a
    // subarray is LTE d, then the number of pairs that have distances <= d
    // can be counted by taking the number of elements in the subarray.
    int n = nums.size();
    std::sort(nums.begin(), nums.end());

    int left = 0;                       // smallest possible distance
    int right = nums[n - 1] - nums[0];  // largest possible distance
    while (left < right) {
      int mid = left + ((right - left) / 2);

      // Count the number of pairs
      int numPairs = countPairs(nums, mid);
      if (numPairs < k) {
        // Since there are less pairs than k, we need to increase the distance,
        // i.e. the kth smallest distance lie in the right half.
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    return left;
  }

  int smallestDistancePairNaive(std::vector<int>& nums, int k) {
    // Naively generate all pairs, sort them by their distances, and return
    // the kth (at index k - 1) distance
    // Time: O(n^2 logn)
    // Space: O(n^2)
    int n = nums.size();
    std::vector<std::pair<int, int>> pairs;
    pairs.reserve(n * (n - 1) / 2);

    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        pairs.push_back({nums[i], nums[j]});
      }
    }

    std::sort(pairs.begin(), pairs.end(),
              [](std::pair<int, int> p1, std::pair<int, int> p2) {
                return std::abs(p1.first - p1.second) <
                       std::abs(p2.first - p2.second);
              });

    return std::abs(pairs[k - 1].first - pairs[k - 1].second);
  }

 private:
  int countPairs(const std::vector<int>& nums, int dist) {
    int count = 0;

    int left = 0;
    for (int right = 0; right < nums.size(); ++right) {
      // Array is sorted => subarray is sorted
      while (nums[right] - nums[left] > dist) {
        // Adjust left pointer to reduce the distance
        ++left;
      }
      // Not (r - l + 1), to compensate for the extra ++left invocation
      // before the while loop breaks.
      count += (right - left);
    }
    return count;
  }
};
