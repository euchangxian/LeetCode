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

constexpr int MOD = 1E9 + 7;
class Solution {
 public:
  int profitableSchemes(int n,
                        int minProfit,
                        std::vector<int>& group,
                        std::vector<int>& profit) {
    // Group of n members, list of various crimes they can comit.
    // ith crime generates profit[i], requires group[i] members to participate.
    // If a member participates in one, then they cannot participate in another.
    // A profitable scheme is any subset of these crimes that generate at least
    // minProfit profit, and the total members participating is at most n.
    // Return the number of schemes that can be chosen, modulo 10E9+7
    //
    // Seems like DP at first glance.
    constexpr std::size_t MAX_N = 100;
  }
};
