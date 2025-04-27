#include <random>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// If n was small enough, we could store [0..n-1]\blacklist in memory, reducing
// this to just a random() call.
// Hm. We can remap integers into the blacklisted spots.
// Suppose blacklist.size = m. Then we can arbitrarily choose m integers not
// in the blacklist. The last m integers in the range [0..n-1]
// Takes at most O(2m) to fill up the map. O(m) worst case if
// n-m < blacklist[i] < n (i.e., all last m integers are blacklisted)
class Solution {
 public:
  Solution(int n, std::vector<int>& blacklist)
      : mt(std::random_device{}()), distr(0, n - 1 - blacklist.size()) {
    const int m = blacklist.size();
    const int ub = n - m - 1;  // pick from [0..n-1-m]

    std::unordered_set<int> blackset{blacklist.begin(), blacklist.end()};
    actual.reserve(m);
    int remap = n - 1;
    for (int excl : blacklist) {
      if (excl > ub) {
        continue;
      }

      while (blackset.contains(remap)) {
        --remap;
      }
      actual[excl] = remap--;
    }
  }

  int pick() {
    int rand = distr(mt);
    if (auto it = actual.find(rand); it != actual.end()) {
      return it->second;
    }
    return rand;
  }

 private:
  std::mt19937 mt;
  std::uniform_int_distribution<> distr;
  std::unordered_map<int, int> actual;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
