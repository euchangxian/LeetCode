#include <cstddef>
#include <cstdlib>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::vector<int> minOperations(std::string_view boxes) {
    // boxes[i] = 0 (empty) | 1 (one ball)
    // In one operation:
    // - Move one ball from a box to an adjacent box. There may be >1 ball in
    //   some boxes.
    // answer[i] is the minimum operation to move all balls to the ith box,
    // stateless.
    //
    // hmmmm.. Naively, for each box, sum the distance of every other box with
    // a ball from that box.
    // How can we do better?
    // Something like a prefix + suffix sum? Sum of distance of balls to the
    // left, plus balls to the right.
    // The sums need to grow proportionately to the number of balls, therefore
    // two states is necessary, sum and numBalls
    // Three pass is needed. Or two, if we update the result at the same time.
    std::vector<int> answer(boxes.size(), 0);

    int preBalls = boxes[0] == '1';
    int prefixSum = preBalls;
    for (int i = 1; i < boxes.size(); ++i) {
      answer[i] = prefixSum;

      preBalls += boxes[i] == '1';
      prefixSum += preBalls;  // each of the ball need to move 1 distance more.
    }

    int sufBalls = boxes.back() == '1';
    int suffixSum = sufBalls;
    for (int i = static_cast<int>(boxes.size()) - 2; i >= 0; --i) {
      answer[i] += suffixSum;

      sufBalls += boxes[i] == '1';
      suffixSum += sufBalls;
    }

    return answer;
  }
};
