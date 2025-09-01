#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <queue>
#include <utility>
#include <vector>

class Solution {
 public:
  double maxAverageRatio(std::vector<std::vector<int>>& classes,
                         int extraStudents) {
    auto calcIncrement = [](const auto& clazz) {
      double pass = clazz[0];
      double total = clazz[1];
      return ((pass + 1) / (total + 1)) - ((pass) / total);
    };

    const auto n = static_cast<int>(classes.size());

    using Node = std::pair<double, int>;
    std::priority_queue<Node> maxHeap;
    for (int i = 0; i < n; ++i) {
      maxHeap.emplace(calcIncrement(classes[i]), i);
    }

    while (extraStudents--) {
      auto [_, idx] = maxHeap.top();
      maxHeap.pop();

      auto& clazz = classes[idx];
      ++clazz[0];
      ++clazz[1];
      maxHeap.emplace(calcIncrement(clazz), idx);
    }

    double sumPassRate = 0.0;
    for (const auto& clazz : classes) {
      double pass = clazz[0];
      double total = clazz[1];
      sumPassRate += pass / total;
    }

    return sumPassRate / classes.size();
  }

  double maxAverageRatioRangesHeap(std::vector<std::vector<int>>& classes,
                                   int extraStudents) {
    auto calcIncrement = [](const auto& clazz) {
      double pass = clazz[0];
      double total = clazz[1];
      return ((pass + 1) / (total + 1)) - ((pass) / total);
    };

    std::ranges::make_heap(classes, {}, calcIncrement);
    while (extraStudents--) {
      std::ranges::pop_heap(classes, {}, calcIncrement);
      auto& clazz = classes.back();
      ++clazz[0];
      ++clazz[1];
      std::ranges::push_heap(classes, {}, calcIncrement);
    }

    double sumPassRate = 0.0;
    for (const auto& clazz : classes) {
      double pass = clazz[0];
      double total = clazz[1];
      sumPassRate += pass / total;
    }

    return sumPassRate / classes.size();
  }

  double maxAverageRatioVec(std::vector<std::vector<int>>& classes,
                            int extraStudents) {
    // first, notice that the smaller the total, the more the extraStudents
    // contribute to the passing rate.
    // second, notice that the smaller the number of students that pass, the
    // more the extraStudents contribute.
    // Might be tempting to argue that the smaller/greater the ratio of
    // pass:total, the more optimal it is to assign the extraStudents to that
    // class.
    // But consider the most straightforward counter-examples:
    // classes = [[1,2], [1, 100000]], extraStudents = 1, or
    // classes = [[1,2], [99'999, 100'000]], extraStudents = 1.
    //
    // The increment in the passing ratio is just one more layer of
    // indirection: new_pass_ratio - original_pass_ratio.
    //
    // Seems like a maxHeap kinda solution.
    auto calcIncr = [](double pass, double total) -> double {
      return ((pass + 1) / (total + 1)) - (pass / total);
    };

    auto cmp = [&calcIncr](const std::vector<int>& a,
                           const std::vector<int>& b) -> bool {
      return calcIncr(a[0], a[1]) < calcIncr(b[0], b[1]);
    };

    std::make_heap(classes.begin(), classes.end(), cmp);
    while (extraStudents--) {
      std::vector<int> best = std::move(classes.front());
      std::pop_heap(classes.begin(), classes.end(), cmp);

      ++best[0];
      ++best[1];
      classes.back() = std::move(best);
      std::push_heap(classes.begin(), classes.end(), cmp);
    }

    double sum = 0.0;
    for (const auto& clz : classes) {
      sum += static_cast<double>(clz[0]) / clz[1];
    }
    return sum / classes.size();
  }
};
