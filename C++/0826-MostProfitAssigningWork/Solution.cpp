#include <algorithm>
#include <ranges>
#include <utility>
#include <vector>

class Solution {
 public:
  int maxProfitAssignment(std::vector<int>& difficulty,
                          std::vector<int>& profit,
                          std::vector<int>& worker) {
    // n jobs, m workers.
    // - difficulty[i] and profit[i]: difficulty/profit of ith job.
    // - worker[j]: ability of jth worker, i.e., can complete a job with
    //   difficulty at most worker[j].
    // Each worker can complete at most 1 job.
    // Each job can be completed by multiple workers.
    // Return the maximum profit possible.
    //
    // Hm. We want to assign the max profit job to each worker.
    // Sort (difficulty, profit), and ability, then two pointers?
    // Prefix Max Profit?
    const auto n = static_cast<int>(difficulty.size());
    std::vector<std::pair<int, int>> prefix;
    prefix.reserve(n);
    for (auto [d, p] : std::views::zip(difficulty, profit)) {
      prefix.emplace_back(d, p);
    }

    std::ranges::sort(prefix);
    for (int i = 1; i < n; ++i) {
      prefix[i].second = std::max(prefix[i].second, prefix[i - 1].second);
    }
    std::ranges::sort(worker);

    int result = 0;
    int i = 0;
    for (auto ability : worker) {
      while (i < n && prefix[i].first <= ability) {
        ++i;
      }

      if (i > 0) {
        result += prefix[i - 1].second;
      }
    }

    return result;
  }
};
