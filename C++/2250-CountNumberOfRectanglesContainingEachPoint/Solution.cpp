#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <tuple>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(n + 1, 0) {}

  int query(int l, int r) const { return prefix(r) - prefix(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += i & -i) {
      tree[i] += diff;
    }
  }

  int prefix(int i) const {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree[i];
    }
    return sum;
  }

 private:
  int N;
  std::vector<int> tree;
};

class Solution {
 public:
  std::vector<int> countRectangles(std::vector<std::vector<int>>& rectangles,
                                   std::vector<std::vector<int>>& points) {
    // rectangles[i] = (x, y) indicating the top-right of a rectangle, starting
    // from (0, 0).
    // points[i] = (i, j).
    // Want: For each point, find out how many rectangles cover it.
    //
    // First glance seems like 2D range queries. But we can simplify this.
    // Notice that for a rectangle with its top-right corner at (x, y), every
    // point i <= x and j <= y will be covered.
    // Very similar to 2736. Maximum Sum Queries, except that there is no need
    // to determine the maximum (sum).
    // Two Fenwick Trees, one for each dimension, take the minimum.
    // NOPE. WA.
    // Consider rectangles = [[1, 10], [10, 1]], points = [[5, 5]]
    // Clearly, the point will not be covered by either rectangle, but
    // the queries will wrongly return 1.
    //
    // 1 <= l, x <= 10e9
    // 1 <= h, y <= 100
    //
    // Hm, we can sort the rectangles/points.
    // Maintain a Fenwick Tree indexed by Y (since X needs to be discretized)
    // Sort rectangles by descending order of x. Similarly, sort points
    // by descending order of x.
    // This is because a rectangle with a large x-coordinate will cover
    // everything smaller, as long as its height is sufficient
    // Then, at each Point(pX, pY), add all rectangles(rX, rY)
    // with rX >= pX, then query for rY >= pY.
    // Wow.
    constexpr int MAX_Y = 100;
    std::vector<std::tuple<int, int, int>> sortedPoints;
    sortedPoints.reserve(points.size());
    for (int i = 0; i < points.size(); ++i) {
      sortedPoints.emplace_back(points[i][0], points[i][1], i);
    }

    std::sort(rectangles.begin(), rectangles.end(), std::greater<>{});
    std::sort(sortedPoints.begin(), sortedPoints.end(), std::greater<>{});

    FenwickTree ftY(MAX_Y + 1);
    std::vector<int> answer(points.size());
    auto itRec = rectangles.begin();
    for (const auto [x, y, idx] : sortedPoints) {
      while (itRec != rectangles.end() && (*itRec)[0] >= x) {
        ftY.update((*itRec)[1] + 1, 1);
        ++itRec;
      }

      answer[idx] = ftY.query(y + 1, MAX_Y + 1);
    }
    return answer;
  }
};
