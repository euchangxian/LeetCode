#include <algorithm>
#include <vector>

class Solution {
 public:
  int minimumEffort(std::vector<std::vector<int>>& tasks) {
    // tasks[i] = [actual, minimum]:
    // - actual is the amount of energy spent to finish the ith task,
    // - minimum is the amount of energy required to begin the ith task.
    // Return the minimum initial amount of energy to finish all the tasks in
    // any order.
    // 1 <= actual <= minimum <= 1E4
    const auto n = static_cast<int>(tasks.size());

    std::ranges::sort(tasks, {}, [](const auto& t) { return t[1] - t[0]; });
    auto result = 0;
    for (auto task : tasks) {
      result = std::max(result + task[0], task[1]);
    }
    return result;
  }
};
