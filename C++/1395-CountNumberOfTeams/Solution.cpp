#include <climits>
#include <vector>

class Solution {
 public:
  // Consider the prefix and postfix elements that are larger/smaller than
  // rating[i]. Multiply to get the result
  int numTeams(const std::vector<int>& rating) {
    int n = rating.size();
    int result = 0;

    for (int mid = 0; mid < n; ++mid) {
      // Consider increasing sequences
      int leftSmaller = 0;
      int rightLarger = 0;

      for (int left = mid - 1; left >= 0; --left) {
        if (rating[left] < rating[mid]) {
          ++leftSmaller;
        }
      }

      for (int right = mid + 1; right < n; ++right) {
        if (rating[right] > rating[mid]) {
          ++rightLarger;
        }
      }

      // Add the number of combinations of increasing sequences
      result += leftSmaller * rightLarger;

      // Consider decreasing sequences
      // since rating is unique, simply take the inverse of each side
      int leftLarger = mid - leftSmaller;
      int rightSmaller = (n - mid - 1) - rightLarger;

      // Add the number of combinations of increasing sequences
      result += leftLarger * rightSmaller;
    }
    return result;
  }

 private:
  void naive(const std::vector<int>& rating,
             int& result,
             int i,
             int count,
             int prev,
             bool isIncreasing) {
    if (count == 3) {
      ++result;
      return;
    }

    if (i >= rating.size()) {
      return;
    }

    // Skip this element
    naive(rating, result, i + 1, count, prev, isIncreasing);

    // Use this element if it maintains the required order
    if (count == 0 || (isIncreasing && rating[i] > prev) ||
        (!isIncreasing && rating[i] < prev)) {
      naive(rating, result, i + 1, count + 1, rating[i], isIncreasing);
    }
  }

  int numTeamsNaive(std::vector<int>& rating) {
    int result = 0;

    // Count increasing sequences
    naive(rating, result, 0, 0, INT_MAX, true);

    // Count decreasing sequences
    naive(rating, result, 0, 0, INT_MIN, false);

    return result;
  }

  int numTeamsNaiveDP(const std::vector<int>& rating) {
    int n = rating.size();

    // dp[i][j] stores the number of increasing/decreasing sequences of length
    // j + 1, ending at index i
    std::vector<std::vector<int>> increasing(n, std::vector<int>(3));
    std::vector<std::vector<int>> decreasing(n, std::vector<int>(3));

    // Initialize base case
    for (int i = 0; i < n; ++i) {
      increasing[i][0] = 1;
      decreasing[i][0] = 1;
    }

    // For each sequence length in {2, 3}
    for (int len = 1; len < 3; ++len) {
      // For each sequence ending with rating[i]
      for (int i = 0; i < n; ++i) {
        // For every subsequent soldier
        for (int j = i + 1; j < n; ++j) {
          // If monotonicity is maintained
          if (rating[j] > rating[i]) {
            increasing[j][len] += increasing[i][len - 1];
          }
          if (rating[j] < rating[i]) {
            decreasing[j][len] += decreasing[i][len - 1];
          }
        }
      }
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
      result += increasing[i][2] + decreasing[i][2];
    }
    return result;
  }
};
