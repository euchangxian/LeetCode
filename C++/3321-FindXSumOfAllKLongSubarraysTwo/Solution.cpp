#include <iterator>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

using i64 = long long;
class Solution {
 public:
  std::vector<long long> findXSum(std::vector<int>& nums, int k, int x) {
    // fixed x-size sliding window.
    // Need at least two heaps. A minHeap to maintain the top-x most frequent,
    // and a maxHeap of the others in the window?
    // At each iteration, determine if a "swap" is needed.
    const auto n = static_cast<int>(nums.size());

    std::unordered_map<int, int> freq;
    freq.reserve(n);

    std::set<std::pair<int, int>> topX;
    std::set<std::pair<int, int>> remaining;

    std::vector<i64> result;
    result.reserve(n - k + 1);
    i64 windowSum = 0;

    auto update = [&](int freq, int num, int newFreq) {
      if (freq == 0) {
        remaining.insert({newFreq, num});
        return;
      }

      const auto key = std::make_pair(freq, num);

      if (auto it = remaining.find(key); it != remaining.end()) {
        auto node = remaining.extract(it);
        if (newFreq) {
          node.value().first = newFreq;
          remaining.insert(std::move(node));
        }

      } else if (auto it = topX.find(key); it != topX.end()) {
        windowSum -= freq * static_cast<i64>(num);

        auto node = topX.extract(it);
        if (newFreq) {
          node.value().first = newFreq;
          topX.insert(std::move(node));
          windowSum += (newFreq) * static_cast<i64>(num);
        }
      }
    };

    for (int i = 0; i < n; ++i) {
      auto prevRFreq = freq[nums[i]]++;
      update(prevRFreq, nums[i], prevRFreq + 1);

      if (i >= k) {
        auto prevLFreq = freq[nums[i - k]]--;
        update(prevLFreq, nums[i - k], prevLFreq - 1);
      }

      if (topX.size() < x && !remaining.empty()) {
        auto top = remaining.extract(std::prev(remaining.end()));
        windowSum += top.value().first * static_cast<i64>(top.value().second);
        topX.insert(std::move(top.value()));
      }

      if (topX.size() >= x && !remaining.empty()) {
        const auto& remTop = *remaining.rbegin();
        const auto& smallestInWindow = *topX.begin();

        if (smallestInWindow < remTop) {
          auto botNode = topX.extract(smallestInWindow);
          windowSum -=
              botNode.value().first * static_cast<i64>(botNode.value().second);

          auto topNode = remaining.extract(remTop);
          windowSum +=
              topNode.value().first * static_cast<i64>(topNode.value().second);

          topX.insert(std::move(topNode));
          remaining.insert(std::move(botNode));
        }
      }

      if (i + 1 >= k) {
        result.push_back(windowSum);
      }
    }

    return result;
  }
};
