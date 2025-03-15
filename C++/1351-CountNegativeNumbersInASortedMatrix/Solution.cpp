#include <algorithm>
#include <functional>
#include <vector>

class Solution {
 public:
  int countNegatives(std::vector<std::vector<int>>& grid) {
    // Two pointer approach (r,c), we increment for each row, the column pointer
    // to the first negative number. The column pointer is maintained across
    // rows.
    // Therefore, only O(r + c) operations is necessary.
    const int n = grid[0].size();
    int count = 0;
    int i = n - 1;
    for (const auto& row : grid) {
      while (i >= 0 && row[i] < 0) {
        --i;
      }
      count += n - (i + 1);
    }
    return count;
  }

  int countNegativesBinarySearch(std::vector<std::vector<int>>& grid) {
    // Linear search works with the constraint.
    // But the matrix is sorted in non-increasing order in both row-wise and
    // column-wise.
    //
    // For the 1D variant, a binary search is necessary to find the range of
    // values which are negative.
    // We can do similarly here in RlogC time, doing binary search on all rows.
    //
    // But this doesnt exploit the column-wise sorted order.
    const int n = grid[0].size();
    int count = 0;
    for (const auto& row : grid) {
      // finds the first negative element index.
      auto it = std::upper_bound(row.begin(), row.end(), 0, std::greater<>{});

      // Then, n-idx would be the number of negative elements in this row.
      count += n - (it - row.begin());
    }
    return count;
  }
};
