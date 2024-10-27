#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<int> asteroidCollision(vector<int>& asteroids) {
    // Positive indicate going right, negative indicate left.
    // Smaller explodes
    // same size => both explode
    // Monotonically increasing stack.
    std::vector<int> stk;
    stk.reserve(asteroids.size());
    for (int asteroid : asteroids) {
      if (asteroid > 0) {
        stk.push_back(asteroid);
        continue;
      }

      // While there are still asteroids going to the right
      // compare the abs values
      while (!stk.empty() && stk.back() > 0) {
        // if less or equal, asteroid does not survive.
        if (-asteroid <= stk.back()) {
          if (-asteroid == stk.back()) {
            stk.pop_back();
          }

          // Order matters, since we are mutating
          asteroid = 0;
          break;
        }

        // Asteroid survives collision
        if (-asteroid > stk.back()) {
          stk.pop_back();
        }
      }

      if (asteroid != 0) {
        stk.push_back(asteroid);
      }
    }

    return stk;
  }
};
