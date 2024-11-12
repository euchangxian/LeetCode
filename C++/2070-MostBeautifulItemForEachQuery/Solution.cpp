#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> maximumBeauty(std::vector<std::vector<int>>& items,
                                 std::vector<int>& queries) {
    // sort and pre-compute the prefix maximum beauty of price[i]
    std::sort(items.begin(), items.end());
    for (int i = 1; i < items.size(); ++i) {
      items[i][1] = std::max(items[i][1], items[i - 1][1]);
    }

    for (int i = 0; i < queries.size(); ++i) {
      // we want price <= queries[i]
      // for std::upper_bound, given bool(comp(value, *iter)), we are checking
      // if value < *iter  is true => *iter > value is true
      //
      // Side note: for std::lower_bound, given bool(comp(*iter, value)), we are
      // checking if *iter < value is false => *iter >= value is true.
      auto it = std::upper_bound(
          items.begin(), items.end(), queries[i],
          [](int target, std::vector<int>& item) { return target < item[0]; });

      if (it == items.begin()) {
        queries[i] = 0;
      } else {
        --it;
        queries[i] = (*it)[1];
      }
    }
    return queries;
  }
};
