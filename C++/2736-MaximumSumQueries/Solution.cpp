#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <ranges>
#include <utility>
#include <vector>

class SegmentTree {
 public:
  SegmentTree(const std::vector<int>& data) : N(data.size()), tree(4 * N, 0) {
    build(data, 1, 0, N - 1);
  }

  int query(int l, int r) const { return query_(1, 0, N - 1, l, r); }

 private:
  const int N;
  std::vector<int> tree;

  static constexpr int merge(int a, int b) { return std::max(a, b); }
  static constexpr int left(int i) { return i << 1; }
  static constexpr int right(int i) { return (i << 1) + 1; }

  void build(const std::vector<int>& data, int idx, int L, int R) {
    if (L == R) {
      tree[idx] = data[L];
      return;
    }

    int mid = (L + R) / 2;
    build(data, left(idx), L, mid);
    build(data, right(idx), mid + 1, R);

    tree[idx] = merge(tree[left(idx)], tree[right(idx)]);
  }

  int query_(int idx, int L, int R, int l, int r) const {
    if (l > r) {
      return 0;
    }

    if (l <= L && R <= r) {
      return tree[idx];
    }

    int mid = (L + R) / 2;
    return merge(query_(left(idx), L, mid, l, std::min(r, mid)),
                 query_(right(idx), mid + 1, R, std::max(l, mid + 1), r));
  }
};

class Solution {
 public:
  std::vector<int> maximumSumQueries(std::vector<int>& nums1,
                                     std::vector<int>& nums2,
                                     std::vector<std::vector<int>>& queries) {
    // queries[i] = [x, y], such that for the ith query,
    // find the maximum value of nums1[j] + nums2[j], with the constraint that
    // nums1[j] >= x and nums2[j] >= y.
    //
    // Hm..
    // Use values as index. Then, we are able to satisfy the constraint of
    // finding >= x or >= y. But RMQ, Range sums, can not inform us of the
    // index j.
    //
    // Seems tough. Common range query patterns wont really work easily, since
    // there seems to be two axes required: index and value.
    // Though, given offline queries, can we preprocess them in a way to enable
    // range queries?
    //
    // Wew, visualize as points on a 2D grid, (nums1, nums2).
    // Take for example: nums1 = [3, 2, 5, 7], nums2 = [2, 3, 4, 3].
    // With nums1 on the x-axis, nums2 on the y-axis, we have something that
    // looks like:
    // ^
    // |          c
    // |  a          d
    // |     b
    // |---------------->
    // where a = (2, 3), b = (3, 2), c = (5, 4), d = (7, 3)
    //
    // Observe that when we sort points according to the x-axis, any points
    // that are lower, i.e., have a smaller y-value, are "useless/redundant".
    // points a and b can be removed, since point c can be used in place of
    // a and b, for any query.
    // Point d can not be removed, since queries like (5, 3), can not be
    // answered by point c, but by point d.
    // Though, in this case, for queries like (5, 3), point d would actually
    // give a higher sum.
    //
    // Thus, with this, we can preprocess nums1 and nums2 to remove redundant
    // points.
    // How can we answer the queries efficiently though?
    // Range maximum? Only insert useful points, with the x-axis, i.e., nums1
    // as the index. Then query(x, MAX_X) for maximum y?
    // No. The sum (x, y) may not be monotonic. i.e., maximum y does not imply
    // maximum sum x + y, since after preprocessing,
    //
    // For preprocessing, we want to sort in descending order of x, then
    // remove points such that the remaining points are
    // - monotonically decreasing in x,
    // - montoonically increasing in y.
    // Lets call these remaining points A.
    // Then, to answer a query (x, y), we search for the largest index r in A
    // such that A[r].x >= x. All smaller indices will satisfy the x-constraint.
    // Then, search for the smallest index l in A such that A[l].y >= y.
    // The points between [l, r] will all satisfy the constraint. We want the
    // maximum.
    // Thus, a Range Maximum Query with a Seg tree will do.
    // Though there are no updates to the data, prefix maxs do not have an
    // inverse, and cannot answer such range maximum queries.
    const int n = nums1.size();

    std::vector<std::pair<int, int>> points =
        std::ranges::views::zip(nums1, nums2) |
        std::ranges::to<std::vector<std::pair<int, int>>>();
    std::sort(points.begin(), points.end(), std::greater<>{});

    std::vector<int> sums;
    sums.reserve(n);
    std::vector<int> X, Y;
    X.reserve(n), Y.reserve(n);
    int maxY = INT_MIN;
    for (const auto [x, y] : points) {
      if (y > maxY) {
        maxY = y;
        X.emplace_back(x);
        Y.emplace_back(y);
        sums.emplace_back(x + y);
      }
    }

    SegmentTree st(sums);
    std::vector<int> answer;
    answer.reserve(queries.size());
    for (const auto& query : queries) {
      const int x = query[0];
      const int y = query[1];

      // NOTE: X is monotonically decreasing. Hence the std::greater comparator.
      auto itR = std::lower_bound(X.rbegin(), X.rend(), x);
      if (itR == X.rend()) {
        answer.push_back(-1);
        continue;
      }

      // Very very unfamiliar behaviour.
      // Index:  0  1  2  3
      // X:      7  5  3  2
      // Suppose we do lower_bound(..., 3).
      // itR would then point to index 2, while rbegin points at index 3.
      // Doing std::distance would then return 1, which points to 5, and is the
      // wrong direction.
      int r = X.size() - 1 - std::distance(X.rbegin(), itR);

      auto itL = std::lower_bound(Y.begin(), Y.end(), y);
      if (itL == Y.end()) {
        answer.push_back(-1);
        continue;
      }
      int l = std::distance(Y.begin(), itL);

      if (l > r) {
        answer.push_back(-1);
      } else {
        answer.push_back(st.query(l, r));
      }
    }

    return answer;
  }
};
