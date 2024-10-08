#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 private:
  int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
      result *= i;
    }
    return result;
  }

 public:
  // Follows the sequence of Catalan Numbers, which has two rules:
  // 1. "" is in the Set
  // 2. if a and b are in the Set, then (a)b is in the set.
  // Essentially, where f(n) refers to the set where each element has n pairs of
  // parentheses:
  // f(0) = ""
  // f(1) = (f(0))f(0)
  // f(2) = (f(0))f(1), (f(1))f(0)
  // f(3) = (f(0))f(2), (f(1))f(1), (f(2))f(0)
  // ...
  // f(n) = (f(0))f(n-1), (f(1))f(n-2), ..., (f(n-1))f(0)
  vector<string> generateParenthesis(int n) {
    vector<vector<string>> dp(n + 1);
    dp[0] = vector<string>(1, "");

    for (int i = 1; i <= n; ++i) {
      // For every combination of j, (i - 1 - j)
      for (int j = 0; j < i; ++j) {
        for (string const& a : dp[j]) {
          for (string const& b : dp[i - j - 1]) {
            dp[i].push_back('(' + a + ')' + b);
          }
        }
      }
    }
    return dp[n];
  }
};
