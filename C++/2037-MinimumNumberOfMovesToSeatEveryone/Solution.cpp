#include <algorithm>
#include <vector>

class Solution {
 public:
  int minMovesToSeat(std::vector<int>& seats, std::vector<int>& students) {
    std::sort(seats.begin(), seats.end());
    std::sort(students.begin(), students.end());
    int moves = 0;
    for (int i = 0; i < seats.size(); ++i) {
      moves += std::abs(seats[i] - students[i]);
    }
    return moves;
  }
};
