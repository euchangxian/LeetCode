#include <cstddef>
#include <cstdlib>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  bool checkIfExist(std::vector<int>& arr) {
    // Two Sum-like. Rewrite the equation from:
    // arr[i] == 2 * arr[j] to
    // arr[i] / 2 == arr[j].
    // i.e., when checking an element, check if its halve, or its double exists.
    std::unordered_set<int> seen;
    for (int i = 0; i < arr.size(); ++i) {
      bool hasHalve = (arr[i] % 2 == 0) && seen.count(arr[i] / 2);
      bool hasDouble = seen.count(arr[i] * 2);

      if (hasHalve || hasDouble) {
        return true;
      }
      seen.insert(arr[i]);
    }
    return false;
  }
};
