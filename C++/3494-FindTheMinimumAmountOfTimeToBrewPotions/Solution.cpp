#include <algorithm>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 minTime(std::vector<int>& skill, std::vector<int>& mana) {
    // skills[i] indicate the skill of the ith wizard
    // mana[i] indicate the mana capacity of the jth potion.
    // Each potion must pass through all the wizards sequentially to be brewed.
    // Time taken by the ith wizard on the jth potion is skill[i] * mana[j].
    // A potion must be passed immediately to the next wizard, without any
    // stalling. See example for a better example.
    // Return the minimum amount of time for the potions to be brewed.
    //
    // Seems like a complicated pipeline where potions can only start brewing
    // if it does not stall in the pipeline.
    // Seems more like a problem of finding the starting time of each potion.
    // If the skill is higher, more time is necessary for that wizard.
    // Hence, a monotonically non-increasing skills can just be queued as soon
    // as the first wizard is done.
    // Hm. Not really. Its a function of
    // skill[i], skill[i+1] and mana[j], mana[j+1]
    // i.e., time[i][j], time[i][j+1], time[i+1][j], time[i+1][j+1]
    // if time is monotonically non-increasing, then no stalling.
    // Consider prefix sums.
    // E.g.,
    // skill = [1, 5, 2, 4]
    // mana  = [5, 1, 4, 2]
    // time  =  5, 25, 10, 20
    //          1,  5,  2,  4  # takes 8 seconds to reach wizard 3, start t=52
    //          4, 20,  8, 16
    //          2, 10,  4,  8
    const auto n = static_cast<int>(skill.size());
    const auto m = static_cast<int>(mana.size());

    // track when wizard[i] is done working on the potion.
    // wizard[i+1] can start working on the second potion when:
    // - wizard[i+1] is done with the first potion, potion[j]
    // - wizard[i] is done with the second potion, potion[j+1]
    std::vector<i64> done(n + 1, 0);
    for (int j = 0; j < m; ++j) {
      for (int i = 0; i < n; ++i) {
        done[i + 1] = std::max(done[i + 1], done[i]) + mana[j] * skill[i];
      }

      for (int i = n - 1; i > 0; --i) {
        done[i] = done[i + 1] - (mana[j] * skill[i]);
      }
    }
    return done.back();
  }
};
