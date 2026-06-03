#include <algorithm>
#include <ranges>
#include <vector>

class Solution {
 public:
  int earliestFinishTime(std::vector<int>& landStartTime,
                         std::vector<int>& landDuration,
                         std::vector<int>& waterStartTime,
                         std::vector<int>& waterDuration) {
    // Same as 3633
    // landStartTime[i] = earliest time ith land ride can be boarded.
    // landDuration[i] = how long the ith land ride lasts.
    // waterStartTime[j] = earliest time jth water ride can be boarded.
    // waterDuration[j] = how long the jth water ride lasts.
    // A tourist must experience exactly one land and one water ride in either
    // order.
    // - A ride may be started at its opening time or later.
    // - If a ride starts at time t, it ends at t+duration.
    // - Immediately after finishing, the tourist may board (or wait) the other
    //   ride.
    // Return the earliest possible time at which the tourist can finish both
    // rides.
    //
    // Only one tourist, two possible orderings: land->water, water->land
    constexpr int INF = 1E9;
    auto earliestLandEnd = INF;
    for (auto [start, duration] :
         std::views::zip(landStartTime, landDuration)) {
      earliestLandEnd = std::min(earliestLandEnd, start + duration);
    }

    auto result = INF;
    auto earliestWaterEnd = INF;
    for (auto [waterStart, waterDuration] :
         std::views::zip(waterStartTime, waterDuration)) {
      auto waterEnd = waterStart + waterDuration;
      earliestWaterEnd = std::min(earliestWaterEnd, waterEnd);

      // waterStart >= waterEnd => can only start water ride after land
      // waterStart < landEnd => can start before, or after.
      if (waterStart >= earliestLandEnd) {
        result = std::min(result, waterEnd);
      } else {
        result = std::min(result, earliestLandEnd + waterDuration);
      }
    }

    for (auto [landStart, landDuration] :
         std::views::zip(landStartTime, landDuration)) {
      // water -> land
      if (landStart >= earliestWaterEnd) {
        result = std::min(result, landStart + landDuration);
      } else {
        result = std::min(result, earliestWaterEnd + landDuration);
      }
    }

    return result;
  }
};
