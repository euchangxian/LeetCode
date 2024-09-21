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
private:
  void dfs(const int n, vector<int> &result, int curr) {
    if (curr > n) {
      return;
    }

    result.push_back(curr);
    for (int i = 0; i <= 9; ++i) {
      dfs(n, result, (curr * 10) + i);
    }
  }

public:
  vector<int> lexicalOrder(int n) {
    // Recursive DFS solution is of O(logn) (base 10) space, since the maximum
    // depth of the call-tree is of O(logn)
    // Lets do better, using an iterative solution.
    // A stack will still be considered extra space, even if its iterative.
    // Therefore, considering the state required, only the curr number is
    // necessary.
    // We can explore the curr number iteratively,
    vector<int> result;
    result.reserve(n);

    // Start with 1
    int curr = 1;
    for (int i = 1; i <= n; ++i) {
      result.push_back(curr);

      if (curr * 10 <= n) {
        // If still within limit
        curr *= 10;
        continue;
      }

      // Otherwise, move to the next digit (after 1, go to 2)
      // be careful of wrap arounds from 9 -> 0. If that is the case, the tree
      // is at the leaves. Backtrack while the digit is 9, or while the curr is
      // more than n
      while (curr % 10 == 9 || curr >= n) {
        curr /= 10;
      }
      ++curr;
    }

    return result;
  }

  vector<int> lexicalOrderDFS(int n) {
    // Of course we can do better. But how? To do better would mean a time
    // complexity better than O(nlogn).
    // Given constraints of O(n) time and O(1) extra space
    vector<int> result; // result array does not count as extra space.
    result.reserve(n);
    // What about DFS starting from 1? 1 -> 10 -> 100 -> ...
    //                                      11 -> 110 ...
    //                                      12 -> 120 ...
    //                                 2 -> 20 ...
    // Technically, stack frames does kinda count as extra space unless we can
    // tail-call optimize it.

    for (int i = 1; i <= 9; ++i) {
      dfs(n, result, i);
    }

    return result;
  }

  vector<int> lexicalOrderNaive(int n) {
    // Naively, generate a string array from 1 to n. Then simply sort it.
    // O(nlogn)
    vector<int> lexico(n);

    for (int i = 1; i <= n; ++i) {
      lexico[i - 1] = i;
    }

    sort(lexico.begin(), lexico.end(), [&lexico](const int a, const int b) {
      return to_string(a) < to_string(b);
    });

    return lexico;
  }
};
