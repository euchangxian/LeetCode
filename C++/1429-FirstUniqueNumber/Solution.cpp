#include <cstddef>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;
class FirstUnique {
 private:
  std::queue<int> uniq;
  std::unordered_map<int, int> seen;

 public:
  FirstUnique(vector<int>& nums) {
    for (size_t i = 0; i < nums.size(); ++i) {
      ++seen[nums[i]];
      uniq.push(nums[i]);
    }
  }

  // Amortized O(1). Overestimate add() to account for push + pop.
  int showFirstUnique() {
    while (seen[uniq.front()] > 1) {
      uniq.pop();
    }

    if (uniq.empty()) {
      return -1;
    }
    return uniq.front();
  }

  void add(int value) {
    ++seen[value];
    uniq.push(value);
  }
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
