#include <algorithm>
#include <bitset>
#include <deque>
#include <queue>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr int MAX_USERS = 100;
class Solution {
 public:
  std::vector<int> countMentions(
      int numberOfUsers,
      std::vector<std::vector<std::string>>& events) {
    // numberOfUsers, and events of size n * 3.
    // events[i] =
    // | MessageEvent: ["MESSAGE", "timestamp", "mentions_string"]
    //   indicating that a set of users was mentioned in a message at timestamp.
    //   mentions_string =
    //   | id<number>, separated by a single whitespace and may contain
    //     duplicates
    //   | ALL: all users
    //   | HERE: only online users
    // | OfflineEvent: ["OFFLINE", "timestamp", "id"]
    //   representing that user id becomes offline at timestamp for 60 time
    //   units.
    // Return mentions, where mentions[i] represents the number of mentions
    // user i has across all message events.
    // All users are initially online.
    // Status changes are processed before handling any message event that
    // occurs at the same timestamp.
    //
    // How do we count and keep track of ONLINE users and increment them only,
    // efficiently?
    // Seems like numberOfUsers <= 100, while events.length <= 1E5 making it
    // possible to brute force increment for each message,
    // as long as we track of the online/offline status individually.
    std::ranges::sort(events, {}, [](const auto& event) {
      return std::make_pair(std::stoi(event[1]), event[2].front());
    });

    std::vector<int> mentions(numberOfUsers, 0);
    std::bitset<MAX_USERS> isOffline{};

    int allMentions = 0;
    // {id, timestamp}
    std::queue<std::pair<int, int>> offline;
    for (const auto& event : events) {
      auto timestamp = std::stoi(event[1]);

      // process users in the Offline coming Online
      while (!offline.empty() && offline.front().second <= timestamp) {
        isOffline[offline.front().first] = false;
        offline.pop();
      }

      if (auto type = event[0]; type.front() == 'M') {
        // Message Event
        std::string_view mentionsString = event[2];
        if (mentionsString.front() == 'A') {
          ++allMentions;
        } else if (mentionsString.front() == 'H') {
          for (int i = 0; i < numberOfUsers; ++i) {
            if (isOffline[i]) {
              continue;
            }
            ++mentions[i];
          }
        } else {
          for (auto id : mentionsString | std::views::lazy_split(' ') |
                             std::views::transform([](auto&& part) {
                               return std::stoi(part | std::views::drop(2) |
                                                std::ranges::to<std::string>());
                             })) {
            ++mentions[id];
          }
        }
      } else {
        // Offline Event
        auto id = std::stoi(event[2]);
        isOffline[id] = true;
        offline.emplace(id, timestamp + 60);
      }
    }

    for (auto& count : mentions) {
      count += allMentions;
    }
    return mentions;
  }
};
