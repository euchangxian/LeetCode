#include <array>
#include <stack>
#include <vector>

constexpr int MAX_N = 1000;
constexpr int MAX_VAL = 1e4;

class Solution {
 public:
  std::vector<int> nextGreaterElement(std::vector<int>& nums1,
                                      std::vector<int>& nums2) {
    std::array<int, MAX_VAL + 1> nextGreater{};
    std::stack<int> stk;
    for (int j = 0; j < nums2.size(); ++j) {
      while (!stk.empty() && nums2[stk.top()] < nums2[j]) {
        nextGreater[nums2[stk.top()]] = nums2[j];
        stk.pop();
      }
      stk.push(j);
    }

    while (!stk.empty()) {
      nextGreater[nums2[stk.top()]] = -1;
      stk.pop();
    }

    std::vector<int> answer(nums1.size());
    for (int i = 0; i < nums1.size(); ++i) {
      answer[i] = nextGreater[nums1[i]];
    }
    return answer;
  }

  // two scans per element in nums2
  std::vector<int> nextGreaterElementTwoScans(std::vector<int>& nums1,
                                              std::vector<int>& nums2) {
    // for each i in nums1.size,
    // find j such that nums1[i] == nums2[j] and determine the next greater
    // element of nums2[j] in nums2.
    std::array<int, MAX_VAL + 1> index{};
    for (int j = 0; j < nums2.size(); ++j) {
      index[nums2[j]] = j;  // distinct
    }

    std::vector<int> right(nums2.size());
    std::stack<int> stk;
    for (int j = nums2.size() - 1; j >= 0; --j) {
      while (!stk.empty() && nums2[stk.top()] < nums2[j]) {
        stk.pop();
      }
      right[j] = stk.empty() ? nums2.size() : stk.top();
      stk.push(j);
    }

    std::vector<int> answer(nums1.size());
    for (int i = 0; i < nums1.size(); ++i) {
      int j = index[nums1[i]];

      answer[i] = right[j] < nums2.size() ? nums2[right[j]] : -1;
    }
    return answer;
  }
};
