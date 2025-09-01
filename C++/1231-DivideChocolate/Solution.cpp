#include <algorithm>
#include <limits>
#include <vector>

class Solution {
 public:
  int maximizeSweetness(std::vector<int>& sweetness, int k) {
    // sweetness[i] = sweetness of ith chunk of chocolate.
    // Want to share with k friends, make k cuts to get k+1 pieces, where
    // each piece consists of some consecutive chunks.
    // Eat the piece with minimum total sweetness, give the rest to friends.
    // Find the maximum total sweetness you can eat.
    //
    // We want to maximise the sweetness we can get, i.e., the minimum total
    // sweetness of the cuts.
    // First glance seems like Binary Search on the minimum.
    const auto n = static_cast<int>(sweetness.size());

    auto feasible = [&](int minSweetness) {
      int chunks = 0;

      int currSweetness = 0;
      for (int sweet : sweetness) {
        currSweetness += sweet;
        if (currSweetness >= minSweetness) {
          ++chunks;
          currSweetness = 0;
        }
      }
      return chunks >= k + 1;
    };

    int minSweetness = std::numeric_limits<int>::max();
    int sum = 0;
    for (int sweet : sweetness) {
      minSweetness = std::min(minSweetness, sweet);
      sum += sweet;
    }

    int left = minSweetness;
    int right = sum / (k + 1);
    while (left < right) {
      int mid = left + (right - left + 1) / 2;  // ceil div
      if (feasible(mid)) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left;
  }
};
