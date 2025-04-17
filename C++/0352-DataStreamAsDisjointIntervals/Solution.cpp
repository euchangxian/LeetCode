#include <iterator>
#include <map>
#include <utility>
#include <vector>

// Something like TCP buffering. But not really.
//
// Naively, we can represent the ranges as-is, merging as we go along.
// Can we do better?
// A simpler implementation might be line-sweep. Maintain a presence array.
// O(N) for both.
//
// Can we do better? One very visible problem is the re-computation of
// already-merged intervals.
// std::map, with binary search. Then merge with predecessor and successor.
//
// The worst case would be addNum on every even number. O(1).
// Then, every subsequent addNum will cause a merge to happen.
// Worst case is amortized O(1) time per getIntervals. Each addNum will
// on average merge with its left and right intervals.
//
// Though, the returning of the intervals itself will take O(K) time, where
// K is the number of intervals.
// A loose upper-bound is O(N/2) == O(N)
class SummaryRanges {
 public:
  SummaryRanges() {}

  void addNum(int value) {
    // not sure if duplicates are allowed.
    if (intervals.contains(value)) {
      return;
    }

    int left = value;
    int right = value;
    auto successor = intervals.upper_bound(value);
    if (successor != intervals.begin()) {
      auto predecessor = std::prev(successor);
      if (predecessor->second >= value) {
        return;
      }

      if (value - 1 == predecessor->second) {
        left = predecessor->first;
      }
    }

    if (successor != intervals.end() && value + 1 == successor->first) {
      right = successor->second;
      intervals.erase(successor);
    }

    intervals[left] = right;
  }

  std::vector<std::vector<int>> getIntervals() {
    std::vector<std::vector<int>> result;
    result.reserve(intervals.size());

    for (const auto [start, end] : intervals) {
      result.push_back({start, end});
    }
    return result;
  }

 private:
  std::map<int, int> intervals;
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
