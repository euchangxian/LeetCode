#include <string>
#include <string_view>
#include <vector>

constexpr int INF = 1E9;

enum Direction {
  Vertical = '.',
  Left = 'L',
  Right = 'R',
};

class Solution {
 public:
  std::string pushDominoes(std::string_view dominoes) {
    // n dominoes in a line vertically upright.
    // Push some to left/right.
    // Each falling domino pushes dominoes in the same direction.
    // If a vertical domino has dominoes falling on it from both sides,
    // it stays vertical.
    //
    // What about "RL"? Do both become vertical? Seems like "RL" is the answer
    // from running the test cases. i.e., the chain of falling breaks.
    // Hm, equal "force" too. That is to say:
    // "R...L" => "RR.LL",
    // "R....L" => "RRRLLL"
    // i.e., distance matters.
    //
    // Suppose we have a distance array, where a smaller distance indicate a
    // greater force.
    // R....L
    // 012345
    // 543210
    // We can therefore handle both examples above. What if there are
    // interleavings of R/L/V?
    //
    // R..R...L..L
    // 0120123____  (_ indicate INF for simpler comparison)
    // ____3210210
    // Naively, two pass, maintaining the distance from the closest left 'R'.
    // - left-to-right: update the delta of 'V's, i.e., if it falls right.
    // - right-to-left: if delta is 1
    const int n = dominoes.size();
    std::vector<int> distance(n, INF);
    std::string result{dominoes};
    int i = n - 1;
    while (i >= 0) {
      if (dominoes[i] == Direction::Left) {
        --i;

        int d = 1;
        while (i >= 0 && dominoes[i] == Direction::Vertical) {
          result[i] = Direction::Left;
          distance[i--] = d++;
        }
      } else {
        --i;
      }
    }

    i = 0;
    while (i < n) {
      if (dominoes[i] == Direction::Right) {
        ++i;

        int d = 1;
        while (i < n && dominoes[i] == Direction::Vertical) {
          if (d < distance[i]) {
            result[i] = Direction::Right;
          } else if (d == distance[i]) {
            result[i] = Direction::Vertical;
          }
          ++i;
          ++d;
        }
      } else {
        ++i;
      }
    }

    return result;
  }
};
