#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <map>
#include <utility>

// seems like a simple Segment Tree with Lazy Propagation should work.
// Nope. Not very simple. <= 10^9 will definitely cause MLE.
// Will need a Dynamic Segment Tree, i.e., actual nodes and pointers instead
// of static arrays.
//
// A Binary Search Tree is simpler, i.e., Ordered Map.
// Store {left, right}.
//
// When querying a range {left, right},
// use map::upper_bound(left), then std::prev, to get a L <= left.
// Then check if the found `right` covers the queried `right`.
//
// When adding a range {left, right},
// if no range {L, R} such that L <= left and/or right <= R exists, then simply
// insert into the map.
// Otherwise, bookkeeping is necessary.
// map::upper_bound(left), to get any left < L, delete and book-keep.
// NOTE: need to deal with case where the intervals between {left, right} are
// disjoint due to multiple removals.
// Thus, need to find successors and delete while their R <= right.
//
// When deleting a range {left, right},
// map::lower_bound(left), then delete nodes with R <= right.
class RangeModule {
 public:
  RangeModule() {}

  void addRange(int left, int right) {
    auto it = covered.lower_bound(left);

    // while the existing range is partially covered, remove it.
    // We still want to keep track of the maximum possible right.
    // Note the half-open [left, right), we want to merge ranges like
    // [x, y) and [y, z), hence '<='.
    while (it != covered.end() && it->first <= right) {
      right = std::max(right, it->second);

      // NOTE: iterator is not invalidated here, as guaranteed by the Standard.
      // This is in contrast to containers like vector.
      covered.erase(it++);
    }

    // Now, check if we can safely update any ranges with L < left that
    // overlaps with the added range, by using predecessor, i.e., map::prev.
    if (it != covered.begin() && left <= (--it)->second) {
      it->second = std::max(it->second, right);
      return;
    }

    covered[left] = right;
  }

  bool queryRange(int left, int right) {
    auto it = covered.upper_bound(left);
    if (it == covered.begin()) {
      return false;
    }

    --it;
    return right <= it->second;
  }

  void removeRange(int left, int right) {
    // Very similar to add, where we need to do bookkeeping.
    auto it = covered.lower_bound(left);

    // remove any intervals that overlap partially. We want to keep track of
    // any possible intervals (right, existingRight]
    // Note that the range is half-open, [left, right), hence '<', since we
    // do not want to remove [right, xxx).
    int existingRight = -1;
    while (it != covered.end() && it->first < right) {
      existingRight = std::max(existingRight, it->second);
      covered.erase(it++);
    }

    // update any earlier ranges with L < left, and R > left.
    if (it != covered.begin() && left < (--it)->second) {
      existingRight = std::max(existingRight, it->second);
      it->second = left;
    }

    if (right < existingRight) {
      covered[right] = existingRight;
    }
  }

 private:
  std::map<int, int> covered;
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
