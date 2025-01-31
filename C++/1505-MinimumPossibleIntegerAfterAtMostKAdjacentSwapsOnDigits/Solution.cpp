#include <array>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 1) {
    for (int i = 1; i <= N; ++i) {
      int parent = i + (i & -i);
      if (parent <= N) {
        tree[parent] += tree[i];
      }
    }
  }

  int query(int l, int r) const { return query_(r) - query_(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += (i & -i)) {
      tree[i] += diff;
    }
  }

 private:
  const int N;
  std::vector<int> tree;

  int query_(int i) const {
    int sum = 0;
    for (; i > 0; i -= (i & -i)) {
      sum += tree[i];
    }
    return sum;
  }
};

class Solution {
 public:
  std::string minInteger(std::string_view num, int k) {
    // We want to swap the smallest digits to the front, if the number of swaps
    // remaining is sufficient.
    //
    // i.e., "987654321", to bring "1" to the front, "98765432" will need to be
    // shifted right 1, making it a total of 8 swaps.
    //
    // Consider "987654312", only the digits to the left of '1' will be shifted.
    // Then, suppose the prefix "9876543" has been shifted k times ('0's to
    // the left of the to-shift '1', therefore '1' would not have been shifted,
    // initial would look something like "987654320000001").
    // The number of swaps required would thus be lowered by k, pos - k.
    //
    // Therefore, there is a need to keep track of the number of shifts.
    // NOTE: Not RUPQ. We want to maintain a presence array, and iterate left
    // to right, to figure out the number of shifts.
    const int n = num.size();

    // we want to greedily bring the smallest digit, closest to the left, to
    // the front.
    std::array<std::queue<int>, 10> digitPos{};
    for (int i = 0; i < n; ++i) {
      digitPos[num[i] - '0'].push(i);
    }

    FenwickTree ft(n);
    std::string answer;
    answer.reserve(n);
    for (int i = 0; i < n; ++i) {
      for (int d = 0; d <= 9; ++d) {
        if (!digitPos[d].empty()) {
          int idx = digitPos[d].front();

          // 1-indexed, query how many elements to the left of i has been
          // shifted.
          int swaps = ft.query(1, idx);
          if (swaps <= k) {
            digitPos[d].pop();
            k -= swaps;
            answer += (d + '0');

            // right shift by updating the presence array.
            ft.update(idx + 1, -1);
            break;
          }
        }
      }
    }
    return answer;
  }
};
