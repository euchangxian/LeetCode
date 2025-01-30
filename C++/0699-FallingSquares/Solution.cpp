#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(const int n) : N(n), tree(4 * N, 0), lazy(4 * N, -1) {}

  int query(int l, int r) { return query_(1, 0, N - 1, l, r); }

  void update(int l, int r, int val) { update_(1, 0, N - 1, l, r, val); }

 private:
  const int N;

  std::vector<int> tree;
  std::vector<int> lazy;

  static constexpr int left(int i) { return i << 1; }

  static constexpr int right(int i) { return (i << 1) + 1; }

  void propagate_(int idx, int L, int R) {
    if (lazy[idx] == -1) {
      return;
    }

    tree[idx] = lazy[idx];

    // not leaf value, propagate down further.
    if (L != R) {
      lazy[left(idx)] = lazy[idx];
      lazy[right(idx)] = lazy[idx];
    }

    lazy[idx] = -1;
  }

  int query_(int idx, int L, int R, int l, int r) {
    if (l > r) {
      return 0;
    }

    propagate_(idx, L, R);
    if (l <= L && R <= r) {
      return tree[idx];
    }

    int mid = (L + R) / 2;

    return std::max(query_(left(idx), L, mid, l, std::min(mid, r)),
                    query_(right(idx), mid + 1, R, std::max(mid + 1, l), r));
  }

  void update_(int idx, int L, int R, int l, int r, int val) {
    propagate_(idx, L, R);
    if (l > r) {
      return;
    }

    // lazy propagation.
    if (l <= L && R <= r) {
      // Add the new value onto the current maximum height of this segment.
      lazy[idx] = val;
      propagate_(idx, L, R);
      return;
    }

    propagate_(idx, L, R);

    int mid = (L + R) / 2;
    update_(left(idx), L, mid, l, std::min(mid, r), val);
    update_(right(idx), mid + 1, R, std::max(mid + 1, l), r, val);

    tree[idx] = std::max(tree[left(idx)], tree[right(idx)]);
  }
};

class Solution {
 public:
  std::vector<int> fallingSquares(std::vector<std::vector<int>>& positions) {
    // May need to discretize/compress points.
    // Given that each square dropped has two points, (l, r), and that
    // positions.length <= 1000, there will at most be 2000 unique points, as
    // compared to a potential 1 <= (l, r) <= 10^8 + 10^6
    // Also, an integer/32 bit number should be sufficient.
    std::vector<int> points;
    points.reserve(positions.size() * 2);
    for (const auto& position : positions) {
      const int left = position[0];
      const int right = left + position[1] - 1;
      points.push_back(left);
      points.push_back(right);
    }
    std::sort(points.begin(), points.end());

    int k = 0;
    std::unordered_map<int, int> indices;
    indices.reserve(points.size());
    indices[points[0]] = k;
    for (int i = 1; i < points.size(); ++i) {
      if (points[i] != points[i - 1]) {
        indices[points[i]] = ++k;
      }
    }

    SegmentTree st(indices.size());
    int best = 0;
    std::vector<int> answer(positions.size());
    for (int i = 0; i < positions.size(); ++i) {
      const int left = positions[i][0];
      const int right = left + positions[i][1] - 1;

      const int height =
          st.query(indices[left], indices[right]) + positions[i][1];

      st.update(indices[left], indices[right], height);

      best = std::max(best, height);
      answer[i] = best;
    }
    return answer;
  }
};
