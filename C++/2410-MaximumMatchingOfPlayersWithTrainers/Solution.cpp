#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int matchPlayersAndTrainers(std::vector<int>& players,
                              std::vector<int>& trainers) {
    // player[i] can be matched with trainer[j] iff player[i] <= trainer[j]
    // two pointer + greedy.
    std::sort(players.begin(), players.end());
    std::sort(trainers.begin(), trainers.end());

    int matches = 0;
    int i = 0;
    int j = 0;
    while (i < players.size() && j < trainers.size()) {
      if (players[i] <= trainers[j]) {
        ++i;
        ++j;
        ++matches;
      } else {
        ++j;
      }
    }
    return matches;
  }
};
