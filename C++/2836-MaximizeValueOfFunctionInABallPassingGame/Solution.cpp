#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
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

using i64 = long long;
class Solution {
 public:
  i64 getMaxFunctionValue(std::vector<int>& receiver, i64 k) {
    // n players, k passes.
    // Sum of score is i + receiver[i] + receiver[receiver[i]] + ...
    //
    // - receiver may contain duplicates,
    // - receiver[i] may be equal to i (self cycle).
    //
    // Naively, for each starting index i, traverse k times.
    // TLEs with constraints, given k <= 10^10
    //
    // Suppose we have a cycle, then we want to start at the largest index in
    // the cycle to maximize the score of k passes.
    //
    // Okay. Back-track a little. The core of this problem involves looking for
    // cycles, since k can be greater than the number of players.
    // Suppose there are no cycles, then the maximum score is just the sum
    // of indices, 0 + 1 + ... + n-1.
    //
    // However, if there exists cycles, then we want to find the cycle that
    // produces the biggest score.
    //
    // Starting at the biggest index in the cycle is just an optimization.
    // i.e., if we have 2 -> 3 -> 4 -> 2, and k = 3, then we want to start at
    // i=4, such that we get 4 + 2 + 3 + 4.
    //
    // Thereforeeeee, what do we have to keep track of?!
    // Topological sort to remove non-cycle nodes.
    //
    // Need to be careful here though. Suppose the cycle involves lower index
    // nodes, like 1 -> 1, then we want to start from the non-cycle, higher
    // indexed nodes.
    // Therefore, we can track the sum of indices in the topological sort.
    const int n = receiver.size();
    // if k == 1, there is no need to do all these below.
    if (k == 1) {
      return n - 1;
    }

    std::vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
      ++indegree[receiver[i]];
    }

    // initialized to the index.
    // Could use std::iota, i guess.
    std::vector<int> score = [n]() -> std::vector<int> {
      std::vector<int> v(n);
      for (int i = 0; i < n; ++i) {
        v[i] = i;
      }
      return v;
    }();

    std::queue<int> frontier;
    for (int i = 0; i < n; ++i) {
      if (indegree[i] == 0) {
        frontier.push(i);
      }
    }

    // keep track of nodes that has been processed. Small optimization to allow
    // for better space reservation later.
    int processed = 0;
    while (!frontier.empty()) {
      int curr = frontier.front();
      frontier.pop();
      ++processed;

      int next = receiver[curr];
      score[next] = std::max(score[next], score[curr] + next);
      if (--indegree[next] == 0) {
        frontier.push(next);
      }
    }

    // remaining nodes will then be nodes in a cycle. We want to start from
    // higher indexed.
    // We need to keep track of the nodes in the cycle. Can we do without?
    // At most, every player is in the cycle. O(N) extra only.
    for (int start = n - 1; start >= 0; --start) {
      if (indegree[start] == 0) {
        continue;
      }

      i64 cycleSum = 0;
      std::vector<int> cycle;
      cycle.reserve(n - processed);

      int it = start;
      while (indegree[it] > 0) {
        indegree[it] = 0;

        cycleSum += it;
        cycle.push_back(it);

        it = receiver[it];
      }

      // Two cases: k >= cycleLength.
      // In this case, we want to check if the scores from the
      // acyclic nodes + cycle repetition is greater than just purely
      // repeating the cycle.
      //
      // Otherwise, if k < cycleLength.
    }
  }
};
