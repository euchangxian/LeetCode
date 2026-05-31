#include <algorithm>
#include <vector>

class Solution {
 public:
  bool asteroidsDestroyed(int mass, std::vector<int>& asteroids) {
    // original mass of a planet.
    // asteroids[i] is the mass of the ith planet.
    // In any order, arrange collisions. If the mass of the planet is >=
    // asteroid, destroy and absorb the mass. Otherwise, destroy the planet.
    // Return true if all asteroids can be destroyed.
    //
    // Greedy. Sort in ascending order.
    std::ranges::sort(asteroids);

    long long planet = mass;
    for (auto m : asteroids) {
      if (planet < m) {
        return false;
      }
      planet += m;
    }
    return true;
  }
};
