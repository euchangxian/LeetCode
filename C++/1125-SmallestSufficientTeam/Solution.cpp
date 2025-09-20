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

class Solution {
 public:
  std::vector<int> smallestSufficientTeam(
      std::vector<std::string>& req_skills,
      std::vector<std::vector<std::string>>& people) {
    // Given a list of required skills req_skills, and a list of people,
    // where people[i] represents the list of skill the ith person has.
    // Return smallest team that has all the required skills,
    // such that teams = {i, ..., k} where i is the ith person.
    //
    // First, notice the constraints.
    // req_skills.length <= 16
    // people.length <= 60
    // people[i].length <= 16
    // This suggests bitmasking is valid.
    //
    // To get a sufficient team is simple. Simply represent the required skills
    // as a mask, maintain a running mask, and check when its equal.
    // But for the minimum team, not straightforward.
    //
    // Not sure how to break this down in a recursive/naive manner, to arrive
    // at the DP solution.
  }
};
