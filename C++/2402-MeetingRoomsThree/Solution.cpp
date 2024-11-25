#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>

class Solution {
 public:
  int mostBooked(int n, std::vector<std::vector<int>>& meetings) {
    // given n rooms numbered from 0 to n-1.
    // 2D meetings, where meetings[i] = [start, end) (excludes end)
    // All the values of start are unique.
    //
    // Meetings are allocated in the manner:
    // 1. Each meeting takes place in the unused room with the lowest number
    // 2. If there are no available rooms, meeting will be delayed until a room
    //    becomes available. The duration remains the same.
    // 3. When a room becomes unused, meetings that have an earlier original
    //    start time should be given the room.
    //
    // Return the number of the room that held the most meetings.
    //
    // First intuition is to use a priority queue to store room numberes.
    // Sort the meetings by start time.
    // Iterate through the first n meetings and attach them to a room.
    //
    // Therefore, the priority queue should probably store {endTime, roomNum}?
    // Allows us to pop the earliest ending meeting so we can push the next
    // meeting. At most n items in the priority queue.
    std::sort(meetings.begin(), meetings.end());

    std::vector<int> roomsUsage(n, 0);
    std::priority_queue<int, std::vector<int>, std::greater<>> availableRooms;
    for (int i = 0; i < n; ++i) {
      availableRooms.push(i);
    }

    std::priority_queue<std::array<long long, 2>,
                        std::vector<std::array<long long, 2>>, std::greater<>>
        occupied;

    for (int i = 0; i < meetings.size(); ++i) {
      long long start = meetings[i][0];
      long long end = meetings[i][1];
      long long duration = end - start;

      // Pop all ended meetings
      while (!occupied.empty() && occupied.top()[0] <= start) {
        availableRooms.push(occupied.top()[1]);
        occupied.pop();
      }

      // indicates that the current meeting needs to be delayed.
      if (availableRooms.empty()) {
        auto [newStartTime, room] = occupied.top();
        occupied.pop();

        // calculate the new end time.
        occupied.push({newStartTime + duration, room});
        ++roomsUsage[room];
      } else {
        int room = availableRooms.top();
        availableRooms.pop();

        occupied.push({end, room});
        ++roomsUsage[room];
      }
    }

    return std::distance(
        roomsUsage.begin(),
        std::max_element(roomsUsage.begin(), roomsUsage.end()));
  }
};
