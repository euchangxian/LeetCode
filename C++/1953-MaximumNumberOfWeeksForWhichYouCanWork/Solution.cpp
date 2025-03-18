#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

class Solution {
 public:
  long long numberOfWeeks(std::vector<int>& milestones) {
    int n = milestones.size();

    // Suppose that the most milestones is 10. The subsequent have 9 milestones.
    // Regardless of the rest, the number of weeks that can be done without
    // violating the conditions will be limited by the most milestones,
    // and is represented by the total sum of milestones (not including the
    // most), multiplied by 2, add 1 since the mostMilestones can be done 1
    // more time.
    int mostMilestones =
        *std::max_element(milestones.begin(), milestones.end());

    long long totalMilestones =
        std::reduce(milestones.begin(), milestones.end(), 0LL, std::plus<>{});
    long long otherMilestones =
        totalMilestones - static_cast<long long>(mostMilestones);

    return std::min(totalMilestones, otherMilestones * 2 + 1);
  }
};
