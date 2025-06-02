#include <algorithm>
#include <utility>
#include <vector>

class Solution {
 public:
  int candy(std::vector<int>& ratings) {
    // n children, ratings[i] indicate the rating of the ith child.
    // Distribute candies such that:
    // - each child has at least one candy,
    // - children with a higher rating have more candies than their neighbours.
    // Return the minimum number of candies to have.
    //
    // Feels like topological sort of some sorts, then greedily assign.
    // Note the wording though: neighbours. Does this mean that a child with
    // a higher rating may not necessarily have more candies than a child with
    // less rating, if they are not neighbours?
    // ratings = [10, 1, 2, 3]
    // candies = [2, 1, 2, 3] ==> minimum 8.
    //
    // Hm. Still does feels like Greedy. Add all minimum nodes.
    // ratings = [10, 1, 3, 2]
    // Explore 1, mark 10, 3.
    // Explore 2, still unmarked.
    // Ah. BFS-like I guess. We can keep track of the minimum candies required.
    const int n = ratings.size();

    std::vector<std::pair<int, int>> children;
    children.reserve(n);
    for (int i = 0; i < n; ++i) {
      children.emplace_back(ratings[i], i);
    }

    std::ranges::sort(children, {}, &std::pair<int, int>::first);

    int candies = 0;
    std::vector<int> dist(n, 1);
    for (const auto [rating, idx] : children) {
      candies += dist[idx];

      if (idx - 1 >= 0 && rating < ratings[idx - 1]) {
        dist[idx - 1] = std::max(dist[idx - 1], dist[idx] + 1);
      }
      if (idx + 1 < n && rating < ratings[idx + 1]) {
        dist[idx + 1] = std::max(dist[idx + 1], dist[idx] + 1);
      }
    }
    return candies;
  }
};
