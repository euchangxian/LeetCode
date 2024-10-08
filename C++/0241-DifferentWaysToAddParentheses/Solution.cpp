#include <algorithm>
#include <array>
#include <bitset>
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
 public:
  vector<int> diffWaysToCompute(string expression) {
    // Starting small, consider the most simple expression:
    // "2" - There is only one way to compute this, which is 2
    // "2+2" - Only one way: (2 + 2) = 4
    // "2+2*3" - With two operators, parentheses can be placed to produce two
    //          ways: (2 + 2) * 3 = 12, or 2 + (2 * 3) = 8
    // "2+2*3-4" - five ways: ((2 + 2) * 3) - 4 = 8, (2 + (2 * 3)) - 4 = 4
    //                        2 + ((2 * 3) - 4) = 4, 2 + (2 * (3 - 4)) = 0
    //                        (2 + 2) * (3 - 4) = -4
    // Naively, the pattern seems to be like:
    // 1. If expression is empty, return an empty vector
    // 2. If expression.length() == 1 or 2, return a vector containing the digit
    // 3. Otherwise, traverse the expression, splitting it at operators,
    //    e.g., for "2+2*3", recurse("2"), giving {2},
    //          recurse("2*3") = recurse("2") * recurse("3") = {6}
    //          Combining, for each in {2}, "+" with each in {6}, giving {8}.
    //          Return {8}.
    //          Split on "*", recurse("2+2") = {4}, recurse("3") = 3
    //          Combine to get {12}
    //          Combine {8} and {12} to get {8, 12}
    //
    const size_t n = expression.length();

    // dp[i][j] represents the different ways to compute expression[start:end]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));

    // Base cases.
    for (int i = 0; i < n; ++i) {
      if (isdigit(expression[i])) {
        int digit1 = expression[i] - '0';
        dp[i][i] = {digit1};

        if (i + 1 < n && isdigit(expression[i + 1])) {
          dp[i][i + 1] = {(digit1 * 10) + (expression[i + 1] - '0')};
        }
      }
    }

    // Try each substring of length >= 3
    for (int len = 3; len <= n; ++len) {
      for (int start = 0; start + len - 1 < n; ++start) {
        int end = start + len - 1;

        // Iterate through the substring, splitting at operators
        for (int i = start; i <= end; ++i) {
          if (isdigit(expression[i])) {
            continue;
          }

          vector<int>& left = dp[start][i - 1];
          vector<int>& right = dp[i + 1][end];

          for (const int& l : left) {
            for (const int& r : right) {
              switch (expression[i]) {
                case '+':
                  dp[start][end].push_back(l + r);
                  break;
                case '-':
                  dp[start][end].push_back(l - r);
                  break;
                case '*':
                  dp[start][end].push_back(l * r);
                  break;
              }
            }
          }
        }
      }
    }

    return dp[0][n - 1];
  }

  // Notice the repeated computation of expression[start : end]
  // O(n * 2^n) time. Still dominated by the recursive split on each operator
  // O(n^2 + 2^n) space. Extra n^2 to store memo array
  //
  // vector<vector<vector<int>>> memo(n, vector<vector<int>>(n));
  // return diffWaysMemo(expression, memo, 0, n - 1);
  vector<int> diffWaysMemo(const string& expression,
                           vector<vector<vector<int>>>& memo,
                           int start,
                           int end) {
    if (!memo[start][end].empty()) {
      return memo[start][end];
    }

    if (start > end) {
      return {};
    }

    if (end - start + 1 < 3) {
      return {stoi(expression.substr(start, end - start + 1))};
    }

    vector<int> result;
    for (int i = start; i <= end; ++i) {
      if (isdigit(expression[i])) {
        continue;
      }

      // split on operators
      vector<int> left = diffWaysMemo(expression, memo, start, i - 1);
      vector<int> right = diffWaysMemo(expression, memo, i + 1, end);

      for (const int& l : left) {
        for (const int& r : right) {
          switch (expression[i]) {
            case '+':
              result.push_back(l + r);
              break;
            case '-':
              result.push_back(l - r);
              break;
            case '*':
              result.push_back(l * r);
              break;
          }
        }
      }
    }

    // memoize result
    memo[start][end] = result;
    return result;
  }

  // Naive Solution
  // O(n * 2^n) time
  // O(2^n) space
  // diffWaysNaive(expression, 0, n - 1);
  vector<int> diffWaysNaive(const string& expression, int start, int end) {
    if (start > end) {
      return {};
    }

    if (end - start + 1 < 3) {
      return {stoi(expression.substr(start, end - start + 1))};
    }

    vector<int> result;
    for (int i = start; i <= end; ++i) {
      if (isdigit(expression[i])) {
        continue;
      }

      // split on operators
      vector<int> left = diffWaysNaive(expression, start, i - 1);
      vector<int> right = diffWaysNaive(expression, i + 1, end);

      for (const int& l : left) {
        for (const int& r : right) {
          switch (expression[i]) {
            case '+':
              result.push_back(l + r);
              break;
            case '-':
              result.push_back(l - r);
              break;
            case '*':
              result.push_back(l * r);
              break;
          }
        }
      }
    }
    return result;
  }
};
