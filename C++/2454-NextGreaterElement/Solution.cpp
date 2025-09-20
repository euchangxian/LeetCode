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

class Solution {
 public:
  std::vector<int> secondGreaterElement(std::vector<int>& nums) {
    std::unordered_map<int, std::vector<int>> nextGreater;
    std::stack<int> s;
    for (int i = 0; i < nums.size(); ++i) {
      while (!s.empty() && nums[s.top()] < nums[i]) {
        nextGreater[s.top()].push_back(i);
        s.pop();
      }
      s.push(i);
    }

    while (!s.empty()) {
      nextGreater[s.top()].push_back(-1);
      s.pop();
    }

    std::vector<int> answer(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
      auto& indices = nextGreater[nums[i]];
      int j =
          std::lower_bound(indices.begin(), indices.end(), i) - indices.begin();

      auto& indices2 = nextGreater[nums[j]];
      int k = std::lower_bound(indices2.begin(), indices2.end(), j) -
              indices2.begin();

      answer[i] = nums[k];
    }
    return answer;
  }
};
