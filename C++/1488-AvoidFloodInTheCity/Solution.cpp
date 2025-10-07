#include <set>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<int> avoidFlood(std::vector<int>& rains) {
    // Infinite number of lakes, initially empty.
    // Raining over an empty lake will fill it. Raining over a filled lake will
    // flood it.
    // rains[i] > 0 indicate it will rain over the rains[i] lake.
    // rains[i] == 0 indicate there are no rains. Choose one lake and dry it.
    // Return ans such that ans[i] is the lake choosen to be dried on the
    // ith day if rains[i] == 0, ans[i] = -1 otherwise.
    // Return empty if not possible to avoid any flood.
    //
    // Kinda need knowledge of future rains[j] to make decision about current
    // rains[i].
    // Note: rains[i] <= 1E9
    const auto n = static_cast<int>(rains.size());
    std::vector<int> result(n, 1);

    std::unordered_map<int, int> filled;
    filled.reserve(n);

    std::set<int> availableDryDays;
    for (int day = 0; day < n; ++day) {
      auto lake = rains[day];

      if (lake == 0) {
        availableDryDays.emplace_hint(availableDryDays.end(), day);
        continue;
      }

      result[day] = -1;
      if (auto fillDayIt = filled.find(lake); fillDayIt != filled.end()) {
        auto fillDay = fillDayIt->second;

        // find any day >= the previous rain day, so we can dry it before it
        // floods.
        auto dryDay = availableDryDays.lower_bound(fillDay);
        if (dryDay == availableDryDays.end()) {
          return {};
        }

        result[*dryDay] = lake;
        availableDryDays.erase(dryDay);
      }
      filled[lake] = day;
    }

    return result;
  }
};
