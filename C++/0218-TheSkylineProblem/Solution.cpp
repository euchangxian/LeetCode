#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <set>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::vector<int>> getSkyline(
      std::vector<std::vector<int>>& buildings) {
    // buildings[i] = [left, right, height], indicating the height of the
    // building from the x-coordinates [left..right] inclusive.
    // Intervals => Line-Sweep (intuition is straightforward with knowledge of
    // Line-Sweep techniques)
    //
    // Essentially, collect the height at each points on a Line. Sweep through
    // the line, maintaining a maxStack ADT.
    // Use a std::multiset as the MaxStack, as it allows for efficient random
    // erasure.

    // {x, isLeft, height} => sorting would prioritise earlier x-coordinates,
    // tie-broken by ordering startPoints earlier, so that the algorithm will
    // not wrongly mistake a point as having no buildings,
    // and further tie-broken by height, where taller heights are preferred.
    // NOTE:
    // - heights need to be negated to sort in descending order.
    //   This means when processing, it needs to be negated again.
    // - We can omit the isLeft, by using negative heights to mean left, and
    //   positive heights to mean right, maintaining the desired sorted order.
    std::vector<std::pair<int, int>> points;
    points.reserve(buildings.size() * 2);
    for (const auto& building : buildings) {
      points.emplace_back(building[0], -building[2]);

      // NOTE: no need to +1. We want to process this removal of height to
      // denote a new change of max height at the current x-coordinate.
      // See picture on LeetCode.
      points.emplace_back(building[1], building[2]);
    }
    std::sort(points.begin(), points.end());

    // size should be 2 * buildings in the worst case, where there are no
    // overlaps.
    std::vector<std::vector<int>> answer;
    answer.reserve(buildings.size() * 2);
    std::multiset<int> heights;
    int prevHeight = -1;
    for (auto [x, height] : points) {
      // NOTE: we want to process all matching x-coordinates at once, since
      // each iteration may mutate the answer.
      if (height < 0) {
        height *= -1;
        heights.insert(height);
      } else {
        // WARNING: multiset/map::erase(key) removes all elements matching
        // the key...
        // Either use the overload erase(iterator), or C++17 extract(key)...
        heights.extract(height);
      }

      const int top = heights.empty() ? 0 : *heights.rbegin();
      if (top != prevHeight) {
        answer.push_back({x, top});
        prevHeight = top;
      }
    }

    return answer;
  }
};
