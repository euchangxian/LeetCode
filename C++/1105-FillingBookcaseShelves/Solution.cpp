#include <algorithm>
#include <climits>
#include <vector>

class Solution {
 public:
  int minHeightShelves(std::vector<std::vector<int>>& books, int shelfWidth) {
    int n = books.size();

    // dp[i][j] represents the minimum height of the bookshelf after placing the
    // first i books
    std::vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    int currentHeight = 0;
    for (int i = 1; i < n + 1; ++i) {
      // there are two choices for each book: place on the current shelf if the
      // width allows, or place on the next shelf
      // if placing on the current shelf, find the maximum height of the
      // sequence of books that fit on the shelf
      int width = 0;
      int height = 0;

      // for each book starting from the current, try to add to the next shelf
      for (int j = i - 1; j >= 0; --j) {
        width += books[j][0];
        if (width > shelfWidth) {
          break;
        }

        height = std::max(height, books[j][1]);
        dp[i] = std::min(dp[i], dp[j] + height);
      }
    }
    return dp[n];
  }
};
