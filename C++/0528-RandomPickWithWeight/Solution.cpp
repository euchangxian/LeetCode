#include <cstddef>
#include <functional>
#include <iterator>
#include <random>
#include <vector>

using namespace std;
/**
 * w[i] describes the weight of the ith index.
 *
 * implement pickIndex which randomly picks an index in the range [0..n].
 * Probability of picking an index is w[i] / sum(w)
 *
 * Naively, precompute the sum of weights.
 *
 * pickRandom will return a random number in the range [1..sum(w)] inclusive
 * Iterate through and minus w[i] from sum(w). Return when <= 0.
 *
 * Can we do better?
 */
class Solution {
 private:
  const int sumW;
  std::vector<int> prefixW;  // to enable binary search
  std::mt19937 rng;
  std::uniform_int_distribution<int> distr;

 public:
  Solution(vector<int>& w)
      : sumW(std::reduce(w.begin(), w.end(), 0, plus<>{})),
        prefixW(w),
        rng(std::random_device{}()),
        distr(1, sumW) {
    for (size_t i = 1; i < prefixW.size(); ++i) {
      prefixW[i] += prefixW[i - 1];
    }
  }

  int pickIndex() {
    const int target = distr(rng);

    // int left = 0;
    // int right = prefixW.size() - 1;
    // while (left < right) {
    //   int mid = left + (right - left) / 2;
    //
    //   if (prefixW[mid] < target) {
    //     left = mid + 1;
    //   } else {
    //     right = mid;
    //   }
    // }
    //
    // return left;

    return std::distance(
        prefixW.begin(),
        std::lower_bound(prefixW.begin(), prefixW.end(), target));
  }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
