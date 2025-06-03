#include <deque>
#include <vector>

enum State {
  Closed = 0,
  Open = 1,
};

class Solution {
 public:
  int maxCandies(std::vector<int>& status,
                 std::vector<int>& candies,
                 std::vector<std::vector<int>>& keys,
                 std::vector<std::vector<int>>& containedBoxes,
                 std::vector<int>& initialBoxes) {
    // n boxes labelled from 0 to n-1.
    // status[i] = 0|1 (closed|open)
    // candies[i] = number of candies in the ith box.
    // keys[i] = list of boxes that can be opened after opening the ith box.
    // containedBoxes[i] = list of box found in the ith box.
    // Given initialBoxes, take all the candies in any open box, and use the
    // keys in it to open the new boxes, repeatedly.
    // Return the maximum number of candies you can get.
    // - n <= 1000
    // - (containedBoxes|keys)[i].length <= n
    // - Each box is contained one box at most.
    //
    // "maximum"? Feels like simulation at first glance.
    // I guess the difficulty is in data representation for efficient lookup?
    // Feels like (B|D)FS though??
    // Just start with initialBoxes, open all possible boxes.
    // Ah. Think there will be some order of traversal necessary with the box
    // status.
    // i.e., if a box in the current iteration is closed, we may fail to explore
    // it, but opening another box in the same iteration contains the key to
    // that box.
    // Given small constraints, we can use a priority_queue as our frontier.
    // Or a 0/1 Deque, makes more sense.
    const int n = status.size();

    std::deque<int> frontier;
    for (int x : initialBoxes) {
      if (static_cast<State>(status[x]) == State::Open) {
        frontier.push_front(x);
      } else {
        frontier.push_back(x);
      }
    }

    int result = 0;
    while (!frontier.empty()) {
      int curr = frontier.front();
      frontier.pop_front();
      if (static_cast<State>(status[curr]) == State::Closed) {
        break;
      }

      result += candies[curr];
      for (int key : keys[curr]) {
        status[key] = static_cast<int>(State::Open);
      }
      for (int box : containedBoxes[curr]) {
        if (static_cast<State>(status[box]) == State::Open) {
          frontier.push_front(box);
        } else {
          frontier.push_back(box);
        }
      }
    }
    return result;
  }
};
