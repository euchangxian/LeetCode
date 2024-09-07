#include <algorithm>
#include <array>
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
  int leastInterval(vector<char> &tasks, int n) {
    int maxFreq = 0;
    array<int, 26> frequency = {};
    for (auto const &c : tasks) {
      maxFreq = max(maxFreq, ++frequency[c - 'A']);
    }

    // Suppose A occurs 4 times, which is the most, with n = 3:
    // A___ | A___ | A___ | A
    // Thus, we know that at least 3 full rounds are needed to complete A,
    // with a cooldown of 3 cycles.
    //
    // Therefore, we need to figure out how many other tasks have the same
    // frequency as A, since those would be completed in the 4th round too.
    //
    // However, this will only give us the minimal number of CPU cycles
    // required to complete A, without handling the case where we have
    // many unique tasks.
    int rounds = maxFreq - 1;

    int maxFreqCount = 0;
    for (auto const &freq : frequency) {
      maxFreqCount += freq == maxFreq;
    }

    int minCpuCycles = (rounds * (n + 1)) + maxFreqCount;
    return max(minCpuCycles, static_cast<int>(tasks.size()));
  }
};
