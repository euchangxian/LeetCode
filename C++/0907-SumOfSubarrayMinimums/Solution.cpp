#include <cstddef>
#include <cstdlib>
#include <stack>
#include <vector>

using i64 = long long;
constexpr int MOD{1'000'000'007};
class Solution {
 public:
  int sumSubarrayMins(std::vector<int>& arr) {
    // find the sum of min(b), where b ranges over every subarray of arr.
    // Naively, for each element as the start of a subarray, take the min of
    // each subarray.
    // O(n^2).
    //
    // Feels like Sliding Window Minimum, or some sorts.
    // Monotonic non-decreasing Stack.
    // For each minimum in the stack, there is a range of indice in which it
    // is the minimum for.
    // Once we are able to find [l, r] for which arr[i] is the minimum of,
    // this problem can be reduced to a counting problem.
    // Total Subarrays = (i - l + 1) * (r - i + 1)
    // - i - l + 1 ways to choose the start of the subarray.
    // - r - i + 1 ways to choose the end of the subarray.
    // with the constraint that i is included.
    //
    // To find the range [l, r], a monotonically increasing stack can be
    // used to determine l.
    // while a monotonically non-increasing stack can be used to determine r.
    // The different comparisons (> vs >=) are crucial for handling equal
    // elements correctly. Consider an array like [2, 2, 2]:
    // - First 2 should be minimum for subarrays starting at index 0
    // - Second 2 should be minimum for subarrays starting at index 1
    // - Third 2 should be minimum for subarrays starting at index 2
    std::vector<int> left(arr.size());
    std::stack<int> monoStk;
    // determine left boundaries of each minimum.
    for (int i = 0; i < arr.size(); ++i) {
      // Using strictly increasing stack (arr[stack.top()] > arr[i])
      // Equal elements stay in stack, ensuring we choose the leftmost possible
      // boundary for equal elements. This gives each equal element its own
      // distinct set of subarrays where it can be the minimum.
      // WARNING: increasing stack.
      while (!monoStk.empty() && arr[monoStk.top()] > arr[i]) {
        monoStk.pop();
      }

      // if empty, that means this element is the minimum so far.
      left[i] = monoStk.empty() ? 0 : monoStk.top() + 1;
      monoStk.push(i);
    }

    std::vector<int> right(arr.size());
    monoStk = std::stack<int>();
    for (int i = arr.size() - 1; i >= 0; --i) {
      // Using non-increasing stack (arr[stack.top()] >= arr[i])
      // Equal elements are popped, ensuring we choose the rightmost possible
      // boundary before a strictly smaller element. This complements the left
      // boundary calculation to properly partition subarrays among equal
      // elements.
      //
      // The asymmetric handling between left and right stacks (> vs >=) ensures
      // we neither double-count nor miss any subarrays when equal elements are
      // present. WARNING: non-increasing stack.
      while (!monoStk.empty() && arr[monoStk.top()] >= arr[i]) {
        monoStk.pop();
      }

      right[i] = monoStk.empty() ? arr.size() - 1 : monoStk.top() - 1;
      monoStk.push(i);
    }

    int result = 0;
    for (int i = 0; i < arr.size(); ++i) {
      i64 count = 1LL * (i - left[i] + 1) * (right[i] - i + 1);
      result = (result + (1LL * arr[i] * count)) % MOD;
    }
    return result;
  }
};
