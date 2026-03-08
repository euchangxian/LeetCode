#include <algorithm>
#include <array>
#include <functional>
#include <iterator>
#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Each log contains a unique ID and timestamp.
// Timestamp: Year:Month:Day:Hour:Minute:Second, e.g.,
// 2017:01:01:23:59:59
// Each part is zero-padded.
//
// 2000 <= Year <= 2017
// 1 <= Month <= 12
// 1 <= Day <= 31
// 0 <= Hour <= 23
// 0 <= Minute,Second <= 59
class LogSystem {
 public:
  enum Granularity {
    YEAR,
    MONTH,
    DAY,
    HOUR,
    MINUTE,
    SECOND,
    SIZE,
  };

  static constexpr auto REPRS = std::array{
      "Year", "Month", "Day", "Hour", "Minute", "Second",
  };

  static constexpr Granularity parse(std::string_view s) {
    auto it = std::find(REPRS.begin(), REPRS.end(), s);
    auto idx = std::ranges::distance(REPRS.begin(), it);
    return static_cast<Granularity>(idx);
  }

  // 2017:01:01:23:59:59
  //     ^  ^  ^  ^  ^  ^
  //     4  7  10 13 16 19
  static constexpr auto PARTS_END = std::array{
      4,   // year
      7,   // month
      10,  // day
      13,  // hour
      16,  // minute
      19,  // second
  };

  LogSystem() {}

  // Store id, timestamp.
  void put(int id, std::string_view timestamp) { logs.emplace(timestamp, id); }

  // return IDs of the logs that have timestamps within [start..end].
  // Granularity="Year|Month|Day|Hour|Minute|Day", means the parts after can
  // be ignored.
  std::vector<int> retrieve(std::string_view start,
                            std::string_view end,
                            std::string_view granularity) {
    auto g = parse(granularity);
    auto endIdx = PARTS_END[g];
    start = start.substr(0, endIdx);
    end = end.substr(0, endIdx);

    auto endStr = std::string{end};
    ++endStr.back();

    auto startIt = logs.lower_bound(start);
    auto endIt = logs.lower_bound(endStr);

    std::vector<int> result;
    for (auto it = startIt; it != endIt; ++it) {
      result.emplace_back(it->second);
    }
    return result;
  }

 private:
  std::multimap<std::string, int, std::less<>> logs;
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem* obj = new LogSystem();
 * obj->put(id,timestamp);
 * vector<int> param_2 = obj->retrieve(start,end,granularity);
 */
