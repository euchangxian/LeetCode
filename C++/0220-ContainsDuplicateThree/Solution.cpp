#include <cstddef>
#include <cstdlib>
#include <set>
#include <vector>

using namespace std;
class Solution {
 public:
  bool containsNearbyAlmostDuplicate(vector<int>& nums,
                                     int indexDiff,
                                     int valueDiff) {
    // Unlike Contains Duplicate Two, which only has the distance constraint,
    // this has a value constraint, i.e., there is no need for actual
    // duplicates.
    // Naively, check every neighbour that is in the range
    // [nums[i] - k, nums[i] + k].
    // Not viable, since k <= 10^9
    // What about sorting? Wait. Pause, first, we should try to find nearby
    // duplicates. Since |a - a| = 0 is always <= than any valueDiff
    // requirements.
    // If there are no duplicates, then?
    // Ahhhhhh. What about using an ordered_map instead??
    // We first go through to find duplicates. But this time, we maintain the
    // size of the map to only indexDiff+1 elements. Then, we can check the
    // smallest element stored in the map first. If it satisfies the valueDiff,
    // then we found our pairs, since it must also satisfy the indexDiff given
    // the size of the map.
    const int capacity = indexDiff + 1;
    std::set<int> window;

    for (int r = 0; r < nums.size(); ++r) {
      if (window.size() >= capacity) {
        // erase the left of the window, since it wont satisfy indexDiff
        window.erase(nums[r - capacity]);
      }

      // actually, checking the min/max of the ordered set wouldnt work.
      // Consider the sequence [0, 1000, 10 000], valueDiff = 5, nums[r] = 1005.
      // i.e., binary search is more appropriate to find the closest value?
      // lower_bound to find first >= nums[r], take its previous to find the
      // first < nums[r]
      // WARNING: std::lower_bound would do a linear scan instead of the
      // intended binary search on std::set. This is because std::set iterators
      // are bidirectional iterators (a binary search tree underneath the hood),
      // and not random access iterators like std::vectors, std::arrays etc.
      // Therefore, std::set::lower_bound must be used instead.
      auto iter = window.lower_bound(nums[r]);
      if (iter != window.end() && std::abs(*iter - nums[r]) <= valueDiff) {
        return true;
      }

      if (iter != window.begin()) {
        --iter;

        if (std::abs(*iter - nums[r]) <= valueDiff) {
          return true;
        }
      }

      // otherwise, push nums[r] in
      window.insert(nums[r]);
    }
    return false;
  }
};
