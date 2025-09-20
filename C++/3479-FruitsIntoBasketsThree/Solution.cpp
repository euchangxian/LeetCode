#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>

class Solution {
 public:
  int numOfUnplacedFruits(std::vector<int>& fruits, std::vector<int>& baskets) {
    // fruits[i] represent qty of the ith type of fruit,
    // baskets[j] represent the capacity of the jth basket.
    // from left-to-right of fruits:
    // - place each fruit type in the leftmost basket that has a capacity >= qty
    // - Each basket can hold only one type of fruit
    // Return the number of unplaced fruits.
    const auto n = static_cast<int>(fruits.size());
    const auto sqrtN = static_cast<int>(std::sqrt(n));

    std::vector<int> sectorMaxs;
    sectorMaxs.reserve(sqrtN + 1);

    int sectorCount = 0;
    int sectorMax = 0;
    for (int i = 0; i < n; ++i) {
      if (sectorCount >= sqrtN) {
        sectorMaxs.push_back(
            std::exchange(sectorMax, std::numeric_limits<int>::min()));
        sectorCount = 0;
      }

      ++sectorCount;
      sectorMax = std::max(sectorMax, baskets[i]);
    }
    sectorMaxs.push_back(sectorMax);

    int result = n;
    for (int fruitQty : fruits) {
      bool placed = false;

      int sectorIdx = 0;
      for (int start = 0; start < n; start += sqrtN) {
        if (sectorMaxs[sectorIdx] < fruitQty) {
          ++sectorIdx;
          continue;
        }

        for (int basketIdx = start; basketIdx < std::min(start + sqrtN, n);
             ++basketIdx) {
          if (baskets[basketIdx] >= fruitQty) {
            baskets[basketIdx] = 0;
            placed = true;
            break;
          }
        }

        // find new max for this sector
        if (placed) {
          sectorMaxs[sectorIdx] = std::numeric_limits<int>::min();
          for (int basketIdx = start; basketIdx < std::min(start + sqrtN, n);
               ++basketIdx) {
            sectorMaxs[sectorIdx] =
                std::max(sectorMaxs[sectorIdx], baskets[basketIdx]);
          }
          break;
        }
      }

      result -= placed;
    }
    return result;
  }
};
