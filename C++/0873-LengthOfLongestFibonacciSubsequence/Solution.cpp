#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  int lenLongestFibSubseq(std::vector<int>& arr) {
    // A sequence x1, x2, ..., xn is Fibonacci-like if:
    // - n >= 3
    // - xi + xi+1 = xi+2 for all xi+2 <= n
    // Given a strictly increasing array arr, find length of longest
    // fibonacci-like subsequence.
    // Naively, similar to longest increasing subsequence, where
    // dp[i] represents the length of the longest fibonacci-like subsequence
    // ending at arr[i]. Does kinda require O(N^2) search for the previous pairs
    // of elements such that arr[i-2] + arr[i-1] == arr[i].
    // O(N^3), where given N<=1000, TLE.
    // How can we do better! Seems like knowledge of two elements is necessary?
    // Though, we can avoid the O(N) search for arr[i-2], with a two-sum like
    // arr[i] - arr[i-1] == arr[i-2] (Note: wrong notation here. Should be
    // arr[i] - arr[j] == arr[k], where k < j < i)
    const int n = arr.size();

    std::unordered_map<int, int> index;
    index.reserve(n);
    index.emplace(arr[0], 0);

    // dp[j][i] represents the longest fibonacci-like subsequence ending with
    // nums[j], nums[i]
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    int longest = 0;
    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        int first = arr[i] - arr[j];

        // Note the slightly "weird" indexing here.
        auto it = index.find(first);
        if (it != index.end() && it->second < j) {
          dp[j][i] = dp[it->second][j] + 1;
        } else {
          dp[j][i] = 2;  // start a new seq
        }

        longest = std::max(longest, dp[j][i]);
      }
      index.emplace(arr[i], i);
    }

    return (longest >= 3) ? longest : 0;
  }
};
