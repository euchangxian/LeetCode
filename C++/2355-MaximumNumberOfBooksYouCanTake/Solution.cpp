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
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using i64 = long long;
constexpr int INF = 1E9;

class Solution {
 public:
  i64 maximumBooks(std::vector<int>& books) {
    // 0-indexed books[i] indicating number of books on the ith shelf.
    // Take books from a contiguous section books[l..r] such that the number
    // of books taken is strictly increasing.
    //
    // First observation: for each possible contiguous section, there exists an
    // i such that books[i] is completely taken (i.e., the bottleneck).
    // The other indices are possibly not fully taken.
    // Thus, we can derive a naive strategy: For each index i, take books[i].
    // Then take books[i] - d >= 1, and books[i] + d for every shelf d distance
    // away.
    // O(N^2).
    // HMM. NOT CORRECT. We can only guarantee that sum(books[l..i]) is optimal.
    // E.g., {1, 10, 3}. Instead of {1, 2, 3}, we need {1, 10}.
    // Looks like a variant of the maximum sum ending at nums[i].
    const int n = books.size();
  }

  i64 maximumBooksNaive(std::vector<int>& books) {
    const int n = books.size();
    i64 result = 0LL;
    for (int i = 0; i < n; ++i) {
      i64 sum = books[i];
      i64 curr = books[i];
      for (int j = i - 1; j >= 0; --j) {
        curr = std::min(curr - 1, static_cast<i64>(books[j]));
        if (curr <= 0) {
          break;
        }
        sum += curr;
      }

      result = std::max(result, sum);
    }
    return result;
  }
};

int main() {
  std::vector<int> b1{8, 5, 2, 7, 9}, b2{7, 0, 3, 4, 5},
      b3{8, 2, 3, 7, 3, 4, 0, 1, 4, 3}, b4{1, 2, 3, 0, 4};
  std::cout << Solution().maximumBooksNaive(b1) << '\n';
  std::cout << Solution().maximumBooksNaive(b2) << '\n';
  std::cout << Solution().maximumBooksNaive(b3) << '\n';
  std::cout << Solution().maximumBooksNaive(b4) << '\n';
  return 0;
}
