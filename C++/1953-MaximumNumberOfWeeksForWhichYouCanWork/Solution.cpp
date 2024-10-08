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
  long long numberOfWeeks(vector<int>& milestones) {
    int n = milestones.size();

    // Suppose that the most milestones is 10. The subsequent have 9 milestones.
    // Regardless of the rest, the number of weeks that can be done without
    // violating the conditions will be limited by the most milestones,
    // and is represented by the total sum of milestones (not including the
    // most), multiplied by 2, add 1 since the mostMilestones can be done 1
    // more time.
    int mostMilestones = *max_element(milestones.begin(), milestones.end());

    long long totalMilestones =
        reduce(milestones.begin(), milestones.end(), 0LL, plus<>{});
    long long otherMilestones =
        totalMilestones - static_cast<long long>(mostMilestones);

    return min(totalMilestones, otherMilestones * 2 + 1);
  }
};
