#include <algorithm>
#include <array>
#include <string_view>
#include <utility>
#include <vector>

constexpr int MAX_N = 30;
class Solution {
 public:
  int minSwapsCouples(std::vector<int>& row) {
    // n couples sitting in 2n seats, and want to hold hands.
    // row[i] indicate the ID of the person seating in the ith seat. Couples
    // are numbered in order, i.e., (0, 1), (2, 3), ..., (2n-2, 2n-1).
    // Return minimum swaps so that every couple is sitting side-by-side.
    // Feels linkedlist/graph-like.
    // Note that the seating must be even. i.e., we cannot have 2, 0, 1, ...
    // i.e., Couples must be paired starting from seat 0, like 1, 0, 2, ...
    //
    // Does this help us? We kinda need to handle this observation, by treating
    // the pair of seats as one entity/node.
    // Then, each node will have at most two outgoing/incoming edges, to other
    // nodes containing the respective unpaired couples.
    // two edges => two swaps, one edge => 1 swap? or rather, each incoming edge
    // indicate 1 swap? Or rather, avoid double counting by only considering
    // each component once. How to handle "merging" of edges though, i.e.,
    // single edge only.
    //
    // DFS? Preprocess the lookup table of nodes->index. Then swap and simulate?
    // Is there any element of choice involved/optimal swaps? Or does greedy
    // work?
    // Greedy does work.
    // Preprocess O(N)
    std::array<int, 2 * MAX_N> index;
    std::fill(index.begin(), index.end(), -1);
    for (int i = 0; i < row.size(); ++i) {
      index[row[i]] = i;
    }

    int swaps = 0;
    for (int i = 0; i < row.size(); i += 2) {
      int x = row[i];
      int buddy = x ^ 1;
      // very smart way of checking the "buddy". Wow.
      if (row[i + 1] == buddy) {
        continue;
      }

      ++swaps;
      int temp = row[i + 1];
      std::swap(row[index[buddy]], row[i + 1]);

      // Update index array too.
      index[temp] = std::exchange(index[buddy], i + 1);
    }
    return swaps;
  }
};
