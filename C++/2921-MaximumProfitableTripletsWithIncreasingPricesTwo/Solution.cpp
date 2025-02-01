#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

  void update(int i, int val) {
    for (; i <= N; i += i & -i) {
      tree[i] = std::max(tree[i], val);
    }
  }

  int query(int i) const {
    int max = 0;
    for (; i > 0; i -= i & -i) {
      max = std::max(max, tree[i]);
    }
    return max;
  }

  void reset() { std::fill(tree.begin(), tree.end(), 0); }

 private:
  const int N;
  std::vector<int> tree;
};

class SegmentTree {
 public:
  SegmentTree(int n) : N(n), tree(4 * N, 0) {}

  int query(int l, int r) const { return query_(1, 0, N - 1, l, r); }

  void update(int i, int val) { update_(1, 0, N - 1, i, val); }

  void reset() { std::fill(tree.begin(), tree.end(), 0); }

 private:
  const int N;
  std::vector<int> tree;

  template <typename T>
  static constexpr T merge(T a, T b) {
    return std::max(a, b);
  }

  static constexpr int left(int i) { return i << 1; }

  static constexpr int right(int i) { return (i << 1) + 1; }

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

  void update_(int idx, int L, int R, int i, int val) {
    if (L == R) {
      // WARNING: need to ensure duplicate do not override.
      tree[idx] = std::max(tree[idx], val);
      return;
    }

    int mid = (L + R) / 2;
    if (i <= mid) {
      update_(left(idx), L, mid, i, val);
    } else {
      update_(right(idx), mid + 1, R, i, val);
    }

    tree[idx] = merge(tree[left(idx)], tree[right(idx)]);
  }
};

class Solution {
 public:
  int maxProfit(std::vector<int>& prices, std::vector<int>& profits) {
    constexpr int MAX_PRICE = 5000;
    const int n = prices.size();

    std::vector<int> prefix(n, 0);
    SegmentTree st(MAX_PRICE + 1);
    for (int i = 0; i < n; ++i) {
      prefix[i] = st.query(0, prices[i] - 1);
      st.update(prices[i], profits[i]);
    }

    std::vector<int> suffix(n, 0);
    st.reset();
    for (int i = n - 1; i >= 0; --i) {
      suffix[i] = st.query(prices[i] + 1, MAX_PRICE);
      st.update(prices[i], profits[i]);
    }

    int max = -1;
    for (int j = 1; j < n - 1; ++j) {
      if (prefix[j] != 0 && suffix[j] != 0) {
        max = std::max(max, prefix[j] + profits[j] + suffix[j]);
      }
    }
    return max;
  }
  int maxProfitFenwickTree(std::vector<int>& prices,
                           std::vector<int>& profits) {
    // Similar question in CS3233.
    // Fenwick Trees to count index i such that prices[i] < prices[j],
    // and count index k such that prices[j] < prices[k].
    // i.e., iterate left-to-right, then right-to-left.
    // Ok. Don't jump the gun. Hold your horses!
    // We want the maximum profits[i] + profits[j] + profits[k], instead of
    // just the count.
    // Hm. Determining the max profits while also ensuring the constraint holds
    // true is kinda tricky?
    //
    // ...... Suppose we are doing a range query for prices lower than the
    // current considered element. Then, instead of returning the number of
    // indices, we can simply return the maximum profit...
    // Extremely trivial with this observation...
    // Note that Fenwick Tree is not really the best representation to do RMQs.
    // For lower prices, it suffices since we only care about the prefix max,
    // but the non-associativity of max operations make it more difficult for
    // querying higher prices.
    // COULD be circumvented by "negating" the queried price.
    // e.g., instead of doing query(x+1, maxPrice+1), do query(1, maxPrice-x+1),
    // effectively negating.
    //
    // - if prices[k] > prices[j], then, negate and add maxPrice to bring the
    // negative prices to the positive axis, like:
    // maxPrice + 1 - prices[k] < maxPrice + 1 - prices[j].
    //
    // Super smart.
    constexpr int MAX_PRICE = 5000;
    const int n = prices.size();

    std::vector<int> prefix(n, 0);
    FenwickTree ft(MAX_PRICE + 1);
    for (int i = 0; i < n; ++i) {
      prefix[i] = ft.query(prices[i]);
      ft.update(prices[i] + 1, profits[i]);
    }

    std::vector<int> suffix(n, 0);
    ft.reset();
    for (int i = n - 1; i >= 0; --i) {
      int negate = -prices[i] + MAX_PRICE;
      suffix[i] = ft.query(negate);

      ft.update(negate + 1, profits[i]);
    }

    int max = -1;
    for (int j = 1; j < n - 1; ++j) {
      if (prefix[j] != 0 && suffix[j] != 0) {
        max = std::max(max, prefix[j] + profits[j] + suffix[j]);
      }
    }
    return max;
  }
};
