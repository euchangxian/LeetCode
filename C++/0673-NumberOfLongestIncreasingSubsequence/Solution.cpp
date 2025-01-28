#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

template <typename T = std::pair<int, int>>
class PURQ {
 public:
  PURQ(int m) : n_(m), ft_(m + 1, {0, 0}) {}

  // prefix sum
  constexpr T prefix(int i) const { return query(i); }

  // i is 1-indexed.
  constexpr void update(int i, T val) {
    while (i <= n_) {
      if (ft_[i].first < val.first) {
        ft_[i] = val;
      } else if (ft_[i].first == val.first) {
        ft_[i].second += val.second;
      }

      i += i & -i;
    }
  }

 private:
  // i is 1-indexed, as this can only be invoked internally.
  constexpr T query(int i) const {
    T sum = {0, 0};
    while (i > 0) {
      if (sum.first < ft_[i].first) {
        sum = ft_[i];
      } else if (sum.first == ft_[i].first) {
        sum.second += ft_[i].second;
      }
      i -= i & -i;
    }

    return sum;
  }

  std::size_t n_{};
  std::vector<T> ft_;
};

class Solution {
 public:
  int findNumberOfLIS(std::vector<int>& nums) {
    // discretize/compress
    std::vector<int> sorted = nums;
    std::sort(sorted.begin(), sorted.end());

    // 1-indexed.
    int k = 1;
    std::unordered_map<int, int> indices;
    indices.reserve(sorted.size());
    indices[sorted[0]] = k;
    for (int i = 1; i < sorted.size(); ++i) {
      if (sorted[i] != sorted[i - 1]) {
        indices[sorted[i]] = ++k;
      }
    }

    int maxLength = 0;
    int lisCount = 0;

    PURQ<std::pair<int, int>> purq(k);
    for (int num : nums) {
      const int idx = indices[num];

      // query the greatest subsequence length and the respective count of
      // elements smaller than this num.
      auto [len, cnt] = purq.prefix(idx - 1);

      ++len;  // to include the current element in the subsequence.
      if (cnt == 0) {
        cnt = 1;  // start a new sequence ending with this value.
      }

      if (len > maxLength) {
        maxLength = len;
        lisCount = cnt;
      } else if (len == maxLength) {
        lisCount += cnt;
      }

      purq.update(idx, {len, cnt});
    }
    return lisCount;
  }
};
