#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int mincostTickets(std::vector<int>& days, std::vector<int>& costs) {
    // Constraints seems to be very helpful.
    // days is in strictly increasing order.
    // 1 <= days[i] <= 365 ----> days.length <= 365
    // costs.length == 3
    //
    // costs[0] => 1 day
    // costs[1] => 7 days
    // costs[2] => 30 days
    //
    // Greedy approach, based on cost-per-day of passes will not work.
    //
    // Is there a heuristics we can use though?
    // Naively, at each day, brute force all 3 decisions.
    // mincost(days[1..n], costs[1..3]) = min{
    //   mincost(days[i..n], costs[1..3]) + costs[1],
    //   mincost(days[j..n], costs[1..3]) + costs[2],
    //   mincost(days[k..n], costs[1..3]) + costs[3],
    // } adjust the starting index accordingly, based on the number of days
    //   of travel
    // Is there repeated work? Hm, suppose each day is visited more than once,
    // then there WILL be repeated work, i.e., multiple incoming edges to a
    // node.
    // Therefore, we can memoize it to:
    // dp[i] = min cost of travel including the ith day? or days[i]?
    // Doing dp[1..365] would probably be simpler? Or up till days.back?
    //
    // Nope, doing dp[1..365] would wrongly attempt to travel on days that are
    // not necessary, resulting in a possibly higher cost.
    // Or rather... we need to keep track of days we dont travel on.
    constexpr int MAX_DAYS{366};

    const int lastDay = days.back();
    std::array<int, MAX_DAYS> dp{};

    // take advantage of sorted order of days. If day < days[i], we know that
    // the current day is not a day that needs to be travelled. Thus, its cost
    // can be the same as the previous day.
    int i = 0;
    for (int day = 1; day <= lastDay; ++day) {
      if (day < days[i]) {
        dp[day] = dp[day - 1];
        continue;
      }
      ++i;
      dp[day] = std::min({
          dp[day - 1] + costs[0],
          dp[std::max(0, day - 7)] + costs[1],
          dp[std::max(0, day - 30)] + costs[2],
      });
    }

    return dp[lastDay];
  }
};
