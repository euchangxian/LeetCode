#include <string_view>
#include <vector>

class Solution {
 public:
  int bestClosingTime(std::string_view customers) {
    const auto n = static_cast<int>(customers.size());
    auto earliestHour = -1;

    // count 'Y' as positives instead.
    auto maxScore = 0;
    auto score = 0;

    for (int i = 0; i < n; ++i) {
      score += (customers[i] == 'Y') ? 1 : -1;

      if (score > maxScore) {
        maxScore = score;
        earliestHour = i;
      }
    }

    return earliestHour + 1;
  }

  int bestClosingTimeNaive(std::string_view customers) {
    // customers[i] = Y: customers come at ith hour.
    // customers[i] = N: no customers come at the ith hour.
    // If the shop closes at the jth hour, the penalty:
    // - every hour when the shop is open and no customers come: penalty
    //   increases by 1.
    // - every hour when the shop is closed and customers come: penalty
    //   increases by 1.
    // Return the earliest hour at which the shop must be closed to incur a
    // minimum penalty.
    //
    // Treat customers as a binary string, where 1 indicate customers and 0
    // indicate no customers.
    // Then, it becomes like a prefix/suffix.
    //
    // closing at customers[i] indicate that all subsequent 'Y' incur a
    // penalty, and all earlier 'N' incur a penalty.
    // Hence, we need to determine the suffix 'Y', prefix 'N'.
    const auto n = static_cast<int>(customers.size());

    // inclusive of customers[i]
    std::vector<int> suffixY(n + 1);
    suffixY[n - 1] = customers[n - 1] == 'Y';
    for (int i = n - 2; i >= 0; --i) {
      suffixY[i] = suffixY[i + 1] + (customers[i] == 'Y');
    }

    int earliestHour = n;
    int minPenalty = n;
    int prefixN = 0;
    for (int i = 0; i < n; ++i) {
      if (auto penalty = prefixN + suffixY[i]; penalty < minPenalty) {
        earliestHour = i;
        minPenalty = penalty;
      }
      prefixN += customers[i] == 'N';
    }

    if (auto penalty = prefixN; penalty < minPenalty) {
      return n;
    }
    return earliestHour;
  }
};
