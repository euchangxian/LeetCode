#include <cmath>
#include <iterator>
#include <ranges>
#include <tuple>
#include <vector>

class Solution {
 public:
  int countGoodTriplets(std::vector<int>& arr, int a, int b, int c) {
    // given arr, a, b, c
    // A triplet (i, j, k), i < j < k is good if
    // - | arr[i] - arr[j] | <= a
    // - | arr[j] - arr[k] | <= b
    // - | arr[i] - arr[k] | <= c
    // Brute force is trivial: three loops.
    // Can we do better?
    const int n = arr.size();
    int count = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        for (int k = j + 1; k < n; ++k) {
          int diffIJ = std::abs(arr[i] - arr[j]);
          int diffJK = std::abs(arr[j] - arr[k]);
          int diffIK = std::abs(arr[i] - arr[k]);

          if (diffIJ <= a && diffJK <= b && diffIK <= c) {
            ++count;
          }
        }
      }
    }
    return count;
  }

  int countGoodTripletsFunctional(std::vector<int>& arr, int a, int b, int c) {
    const int n = arr.size();

    auto isGood = [a, b, c](const auto& trip) -> bool {
      auto [valI, valJ, valK] = trip;
      int diffIJ = std::abs(valI - valJ);
      int diffJK = std::abs(valJ - valK);
      int diffIK = std::abs(valI - valK);

      return diffIJ <= a && diffJK <= b && diffIK <= c;
    };

    auto good =
        std::views::iota(0, n) | std::views::transform([&arr, n](int i) {
          return std::views::iota(i + 1, n) |
                 std::views::transform([&arr, n, i](int j) {
                   return std::views::iota(j + 1, n) |
                          std::views::transform([&arr, i, j](int k) {
                            return std::make_tuple(arr[i], arr[j], arr[k]);
                          });
                 }) |
                 std::views::join;
        }) |
        std::views::join | std::views::filter(isGood);
    return std::ranges::distance(good);
  }
};
