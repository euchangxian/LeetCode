#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

// One thing to note is that there are no updates to the data. i.e., static
// data.
// Therefore, prefix frequencies work.
// Fenwick/Segment Trees would be overkill. Or maybe not.
// Discretizing the possible values 1 <= arr[i] <= 1e4 is kinda troublesome.
// Furthermore, if an array of size 1e4 were allocated for each index i, then
// it does turn out to be quite expensive.
class SegmentTree {
  using Node = std::unordered_map<int, int>;

 public:
  SegmentTree(const std::vector<int>& arr) : N(arr.size()), st(4 * N) {
    build(arr, 1, 0, N - 1);
  }

  int query(int l, int r, int val) const {
    return query(1, 0, N - 1, l, r, val);
  }

 private:
  const int N{};
  std::vector<Node> st;

  static constexpr int left(int i) { return i << 1; }
  static constexpr int right(int i) { return (i << 1) + 1; }

  void build(const std::vector<int>& arr, int idx, int L, int R) {
    if (L == R) {
      st[idx][arr[L]] += 1;
      return;
    }

    int mid = (L + R) / 2;
    build(arr, left(idx), L, mid);
    build(arr, right(idx), mid + 1, R);

    for (const auto [val, freq] : st[left(idx)]) {
      st[idx][val] += freq;
    }

    for (const auto [val, freq] : st[right(idx)]) {
      st[idx][val] += freq;
    }
  }

  int query(int idx, int L, int R, int l, int r, int val) const {
    if (l > r) {
      return 0;
    }

    if (l <= L && R <= r) {
      auto it = st[idx].find(val);
      return it == st[idx].end() ? 0 : it->second;
    }

    int mid = (L + R) / 2;
    return query(left(idx), L, mid, l, std::min(mid, r), val) +
           query(right(idx), mid + 1, R, std::max(mid + 1, l), r, val);
  }
};

class RangeFreqQuery {
 public:
  RangeFreqQuery(std::vector<int>& arr) {
    occurences.reserve(arr.size());
    for (int i = 0; i < arr.size(); ++i) {
      occurences[arr[i]].push_back(i);
    }
  }

  // Return the frequency of the values in the range [left, right], inclusive.
  int query(int left, int right, int value) {
    auto& indices = occurences[value];

    // find first index >= left.
    // => lower_bound returns first index >= left
    auto lower = std::lower_bound(indices.begin(), indices.end(), left);

    // find last index <= right
    // => upper_bound finds first index > right.
    auto upper = std::upper_bound(indices.begin(), indices.end(), right);

    // indices were 0-indexed, therefore +1. But also need to -1 from the
    // upper_bound's index.
    return std::distance(lower, upper);
  }

 private:
  std::unordered_map<int, std::vector<int>> occurences;
};

class RangeFreqQuerySegmentTree {
 public:
  RangeFreqQuerySegmentTree(std::vector<int>& arr) : values(arr) {}

  // Return the frequency of the values in the range [left, right], inclusive.
  int query(int left, int right, int value) {
    return values.query(left, right, value);
  }

 private:
  SegmentTree values;
};

/**
 * Your RangeFreqQuery object will be instantiated and called as such:
 * RangeFreqQuery* obj = new RangeFreqQuery(arr);
 * int param_1 = obj->query(left,right,value);
 */
