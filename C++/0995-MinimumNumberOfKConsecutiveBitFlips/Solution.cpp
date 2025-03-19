#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

  int prefix(int i) const {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree[i];
    }
    return sum;
  }

  int query(int l, int r) const { return prefix(r) - prefix(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += i & -i) {
      tree[i] += diff;
    }
  }

 private:
  int N;
  std::vector<int> tree;
};

class RUPQ {
 public:
  RUPQ(int n) : N(n), purq(N) {}

  int query(int i) const { return purq.prefix(i); }

  void update(int l, int r, int diff) {
    purq.update(l, diff);
    purq.update(r + 1, -diff);
  }

 private:
  int N;
  FenwickTree purq;
};

class Solution {
 public:
  int minKBitFlips(std::vector<int>& nums, int k) {
    const int n = nums.size();
    int ops = 0;
    std::deque<int> flipped;
    for (int i = 0; i < nums.size(); ++i) {
      // bookkeeping
      if (!flipped.empty() && flipped.front() + k <= i) {
        flipped.pop_front();
      }

      int flips = flipped.size();
      int bit = (nums[i] + flips) % 2;
      if (bit == 0) {
        if (i + k > n) {
          // the last k-1 bit cannot be operated on.
          return -1;
        }

        ++ops;
        nums[i] = 1;
        flipped.push_back(i);
      }
    }
    return ops;
  }

  int minKBitFlipsNaive(std::vector<int>& nums, int k) {
    // Feels like a range update, point query.
    // NOTE: Turns out we can do better! Similar to a sliding window.
    const int n = nums.size();

    int ops = 0;

    // store the number of flips made to nums[i]
    RUPQ ft(n);
    for (int i = 0; i < nums.size(); ++i) {
      int flips = ft.query(i + 1);
      int bit = (nums[i] + flips) % 2;

      if (bit == 0) {
        if (i + k > n) {
          // the last k-1 bit cannot be operated on.
          return -1;
        }

        ++ops;
        nums[i] = 1;
        ft.update(i + 1, i + k, 1);
      }
    }

    return ops;
  }
};
