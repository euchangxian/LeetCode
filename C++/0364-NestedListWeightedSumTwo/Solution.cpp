#include <algorithm>
#include <vector>

#ifdef LOCAL
class NestedInteger {
 public:
  // Constructor initializes an empty nested list.
  NestedInteger();

  // Constructor initializes a single integer.
  NestedInteger(int value);

  // Return true if this NestedInteger holds a single integer, rather than
  // a nested list.
  bool isInteger() const;

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer
  // The result is undefined if this NestedInteger holds a nested list
  int getInteger() const;

  // Set this NestedInteger to hold a single integer.
  void setInteger(int value);

  // Set this NestedInteger to hold a nested list and adds a nested integer
  // to it.
  void add(const NestedInteger& ni);

  // Return the nested list that this NestedInteger holds, if it holds a
  // nested list
  //  The result is undefined if this NestedInteger holds a single integer
  const std::vector<NestedInteger>& getList() const;
};
#endif  // LOCAL

class Solution {
 public:
  int depthSumInverse(std::vector<NestedInteger>& nestedList) {
    // Given a nested list of integers nestedList.
    // Each element is either an integer or a list whose elements may also
    // be integers or other lists.
    // The depth of an integer is the number of lists that it is inside of.
    // maxDepth is the maximum depth of any integer.
    // Weight of an integer is maxDepth - depth + 1.
    // Return the sum of each nestedInteger multiplied by its weight.
    //
    // Two pass DFS? One to get maxDepth, the other to determine the sum.
    // We can factor maxDepth?
    // Let n be the number of integers.
    // result = sum(nums[i] * weight)
    //        = sum(nums[i] * (maxDepth - depth[i] + 1))
    //        = sum(nums[i]*maxDepth + nums[i] - nums[i]*depth[i])
    //        = maxDepth*sum(nums[i]) + sum(nums[i]) - sum(nums[i]*depth[i])
    //        = (maxDepth+1)*sum(nums[i]) - sum(nums[i]*depth[i])
    // Hence, maxDepth is independent of the summation, and result can be
    // obtained in a single pass.
    int maxDepth = 0;
    int sum = 0;
    int productSum = 0;
    auto dfs = [&](this auto&& dfs, const NestedInteger& node, int depth) {
      if (node.isInteger()) {
        maxDepth = std::max(maxDepth, depth);
        sum += node.getInteger();
        productSum += depth * node.getInteger();
        return;
      }

      for (const auto& child : node.getList()) {
        dfs(child, depth + 1);
      }
    };

    for (const auto& node : nestedList) {
      dfs(node, 0);
    }

    return (maxDepth + 1) * sum - productSum;
  }
};
