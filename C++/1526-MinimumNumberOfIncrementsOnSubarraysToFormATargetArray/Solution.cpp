#include <algorithm>
#include <vector>

using namespace std;
class Solution {
public:
  int minNumberOperations(vector<int> &target) {
    // Notice the monotonic-increasing property
    // As target[i] increases, the number of operations increases
    // i.e., {1, 2, 3} => 3 operations required.
    // {3, 1, 2} => 4 operations required
    // Quite similar to counting the left edges that are exposed

    int count{target[0]};
    for (size_t i{1}; i < target.size(); ++i) {
      count += std::max(target[i] - target[i - 1], 0);
    }
    return count;
  }
};
