#include <algorithm>
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
  int lastStoneWeightII(vector<int> &stones) {
    int n = stones.size();

    // dp[i] represents the smallest possible weight given the first i stones
    // The idea is to smash the largest stones together.
    //
    // Turns out this question is a variation of the NP-Complete Partition
    // problem, which is the problem of determining whether an multiset S of
    // positive integers can be partitioned into two subsets S1 and S3 such that
    // the sum of numbers in S1 is equal to that of S2.
    //
    // In this question, the goal is not to determine whether the array can be
    // partitioned equally, but rather to divide the array into two subsets such
    // that the difference between their sums is minimized. I.e., find a subset
    // of stones that has a sum as close as possible to half the total sum.
    int totalSum = 0;
    for (int stone : stones) {
      totalSum += stone;
    }

    // The goal is to get a sum of a subset of stones that is as close to half
    // the sum of the array
    int target = totalSum / 2;

    // dp[i] represents whether a subset with a sum of i can be formed
    vector<bool> dp(target + 1, false);
    dp[0] = true; // A sum of 0 can be formed, by not selecting any stones

    // Maximum sum that is LTE to the Target
    int maxSum = 0;
    for (int stone : stones) {

      // Update the subset sums achievable
      for (int j = stone; j < target + 1; ++j) {
        dp[j] = dp[j] || dp[j - stone];

        if (dp[j]) {
          maxSum = max(maxSum, j);
        }
      }
    }

    // maxSum represents the sum of one subset, e.g. S1
    // sum of S2, s2Sum = totalSum - maxSum
    // difference between S1 and S2 = s2Sum - s1Sum
    //                              = totalSum - 2 * maxSum
    // Note that abs() is not required, since the target is formed by doing
    // integer division / floor of totalSum/2
    return totalSum - (2 * maxSum);
  }
};
