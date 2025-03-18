#include <algorithm>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 numberOfWeeks(std::vector<int>& milestones) {
    const int n = milestones.size();

    // Suppose that the most milestones is 10. The subsequent have 9 milestones.
    // Regardless of the rest, the number of weeks that can be done without
    // violating the conditions will be limited by the most milestones,
    // and is represented by the total sum of milestones (not including the
    // most), multiplied by 2, add 1 since the mostMilestones can be done 1
    // more time.
    i64 mostMilestones = 0;
    i64 totalMilestones = 0;
    for (i64 milestone : milestones) {
      mostMilestones = std::max(mostMilestones, milestone);
      totalMilestones += milestone;
    }

    i64 otherMilestones = totalMilestones - mostMilestones;
    return std::min(totalMilestones, otherMilestones * 2LL + 1LL);
  }
};
