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

class Solution {
 public:
  int minTransfers(std::vector<std::vector<int>>& transactions) {
    // transactions[i] = [from, to, amount], indicating that the person with
    // ID=from gave amount_i to person with ID=to
    // Return the minimum amount of transactions to settle the debt.
    //
    // What debt?? Is this some transitive stuff?
    // Debt is after all the transactions, how much person x owes person y.
    // Note the suspiciously small constraints, which implies DP/backtracking:
    // 1 <= transactions.length <= 8
    // 0 <= from_i, to_i <= 12
    // from_i != to_i
    // 1 <= amount_i <= 100
  }
};
