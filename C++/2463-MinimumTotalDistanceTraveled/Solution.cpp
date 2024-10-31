#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  long long minimumTotalDistance(vector<int>& robot,
                                 vector<vector<int>>& factory) {
    // robot[i] represent the position of the ith robot.
    // factory[j] = {position, limit}, representing the position of the jth
    // factory, and the number of robots that can be repaired.
    //
    // Both robots and factories have unique positions.
    // Robots can start in the same position as a factory.
    //
    // Robots initially move in one direction, negative => left, positive =>
    // right.
    // When a robot reaches a factory that has not reached its limit yet,
    // the factory repairs the robot and it stops moving.
    //
    // The initial direction of movement for robots can be changed.
    // Goal is to minimize the total distance moved by all the robots.
    //
    // INFO:
    // - All robots move at the same speed
    // - Robots won't collide. They will just move past each other.
    // - A factory that has reached its limit is treated as non-existent.
    // - Distance travelled is |x2 - x1| if a robot moves from x1 to x2.
    // - Seems like the total combined capacity of factories may exceed the
    //   number of robots.
    //
    // Hmmmm. Seems like a difficult problem. I do not have any initial
    // intuition.
    // Lets try breaking it down? Seems very much like a DP problem. There are
    // two decisions for each Robot, i.e., deciding whether the robot should
    // move left or move right. There probably isnt a Greedy Choice here,
    // since the closest factory may not be the overall best choice?
    // Do we have a counter example against the Greedy Choice?
    // robots = [0, 3]
    // factory = [[2, 1], [5, 1]]
    // robot[1] starts at x=3, goes left, stops at factory[0]. dist = 1
    // robot[0] starts at x=0, goes right, stops at factory[1]. dist += 5 = 6
    // But if robot[1] goes right to factory[1], and robot[0] goes right to
    // factory[0], then totalDist = |5-3| + |2-0| = 4 < 6.
    // Ok. To make it clear, there is no Greedy Choice where pairing robots
    // with the least distance factory works.
    //
    // The goal is to repair all the robots, i.e., all robots must eventually
    // end at a factory that has capacity, with as little distance travelled.
    //
    // Lets just try naive first then...
    //
    // minDist := 0
    // def dfs(robot, factory, rIdx, currDist):
    //   if rIdx >= robot.size() then minDist = min(minDist, currDist)
    //   for [fPos, fLimit] in factory:
    //     if fLimit > 0 then:
    //       fLimit -= 1
    //       dfs(robot, factory, rIdx + 1, currDist + abs(fPos - robot[rIdx]))
    //       fLimit += 1 // backtrack
    //       dfs(robot, factory, rIdx + 1, currDist)
    //     endif
    // dfs(robot, factory, 0, 0)
    // return minDist
    //
    // Doesnt seem like a need for the notion of left/right?
    // So the decisions are instead M^N, where M is the number of Factories, N
    // is the number of Robots.
    //
    // So what about dp[i][j]? Where dp[i][j] indicates the minimum total
    // distance after assigning the first i robots to the first j factories:

    std::sort(robot.begin(), robot.end());
    std::sort(factory.begin(), factory.end());

    // Replicate each factory by their limit. Allows for easy assignment and
    // advancing of the indices.
    std::vector<int> flatFactories;
    flatFactories.reserve(robot.size() * factory.size());
    for (const std::vector<int>& vec : factory) {
      const int fPos = vec[0];
      const int fLimit = vec[1];
      for (size_t i = 0; i < fLimit; ++i) {
        flatFactories.push_back(fPos);
      }
    }

    constexpr long long INF = 10e9 * 100;
    // dp[i][j] represent the min total distance to assign the first i robots
    // to the first j factories.
    std::vector<std::vector<long long>> dp(
        robot.size() + 1,
        std::vector<long long>(flatFactories.size() + 1, INF));

    // base case: 0 cost to assign 0 robots to any amount of factories.
    for (size_t j = 0; j <= flatFactories.size(); ++j) {
      dp[0][j] = 0;
    }

    for (size_t i = 1; i <= robot.size(); ++i) {
      for (size_t j = i; j <= flatFactories.size(); ++j) {
        long long take =
            dp[i - 1][j - 1] + std::abs(flatFactories[j - 1] - robot[i - 1]);

        // cost of repairing i robots using j-1 factory slots.
        long long skip = dp[i][j - 1];

        dp[i][j] = std::min(take, skip);
      }
    }

    return dp[robot.size()][flatFactories.size()];
  }
};
