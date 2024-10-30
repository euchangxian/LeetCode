#include <algorithm>
#include <cstddef>
#include <numeric>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<long long> maximumCoins(vector<int>& heroes,
                                 vector<int>& monsters,
                                 vector<int>& coins) {
    // The ith hero can defeat the jth monster if monsters[j] <= heroes[i],
    // obtaining coins[j] coins.
    // Return array ans, where ans[i] represent the maximum number of coins
    // that the ith hero can collect.
    //
    // Naively,
    // arr = [0] * n
    // for i in [0..n]: // for each hero
    //   for j in [0..m]: // check each monster
    //     if monsters[j] <= heroes[i] then arr[i] += coins[j]
    // return ans
    //
    // Can we do better than O(n^2)?
    // What about precomputing the maximum score given a power value?
    // O(n) iterate through heroes, get the maximum power. Let this maximum
    // power be maxP.
    // Then iterate through [1..maxP] and then iterate through [0..m] (monsters)
    // and form the coins gained at each power.
    // Then iterate through [0..n] and retrieve P[i].
    // From input constraints, heroes[i] is rather huge, though (10e9).
    //
    // What about sorting?
    // M = [0..m] // indices
    // sort(M) by monsters[m] // ascending Monster Powers.
    // Calculate the prefix sum of coins obtainable, forming something like
    // intervals. Binary search the M array based on Monster Powers?
    // Should be (mlogm + nlogm)
    const size_t n = heroes.size();
    const size_t m = monsters.size();

    std::vector<size_t> monstersIdx(m);
    std::iota(monstersIdx.begin(), monstersIdx.end(), 0);
    std::sort(
        monstersIdx.begin(), monstersIdx.end(),
        [&monsters](size_t i, size_t j) { return monsters[i] < monsters[j]; });

    std::vector<long long> prefixCoinsSum(m, 0);
    prefixCoinsSum[0] = coins[monstersIdx[0]];
    for (size_t i = 1; i < m; ++i) {
      prefixCoinsSum[i] = prefixCoinsSum[i - 1] + coins[monstersIdx[i]];
    }

    std::vector<long long> ans(n, 0);
    for (size_t i = 0; i < n; ++i) {
      // Find the first monster that the hero CANNOT defeat.
      // Calls for std::upper_bound!
      // NOTE:
      // std::lower_bound: comparator is used as bool(comp(*iter, value))
      // i.e., is element < value?
      // std::upper_bound: comparator is used as bool(comp(value, *iter))
      // i.e., is value < element?
      auto it =
          std::upper_bound(monstersIdx.begin(), monstersIdx.end(), heroes[i],
                           [&monsters](int heroPower, size_t mIdx) {
                             return heroPower < monsters[mIdx];
                           });

      // index of the first monster with a higher power.
      size_t mPos = std::distance(monstersIdx.begin(), it);
      if (mPos > 0) {
        ans[i] = prefixCoinsSum[mPos - 1];
      }
    }
    return ans;
  }
};
