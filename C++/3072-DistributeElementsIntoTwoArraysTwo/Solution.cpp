#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(int n) : N(n), tree(N + 1, 0) {}

  int query(int l, int r) const { return query_(r) - query_(l - 1); }

  void update(int i, int diff) {
    for (; i <= N; i += i & -i) {
      tree[i] += diff;
    }
  }

  int query_(int i) const {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
      sum += tree[i];
    }
    return sum;
  }

 private:
  const int N;
  std::vector<int> tree;
};

class Solution {
 public:
  std::vector<int> resultArray(std::vector<int>& nums) {
    // two arrays of size n.
    // Return concatenated, by following the rules:
    // - append first and second number to nums1, nums2 respectively.
    //
    // Define greaterCount(arr, val) -> number of elements in arr that are
    // strictly greater than val.
    //
    // Subsequently,
    // - if greaterCount(nums1, nums[i]) > greaterCount(nums2, nums[i]),
    //   append to nums1.
    // - if less, append to nums2
    // - if equal, append to whichever has less element.
    // - if both have equal elements, then append to nums1.
    //
    // Maintain two Fenwick Trees (presence array). Query and update
    // respectively.
    // Discretization is necessary since nums[i] <= 10^9
    const int n = nums.size();

    std::vector<int> sorted = nums;
    std::sort(sorted.begin(), sorted.end());

    int k = 1;
    std::unordered_map<int, int> rank;
    rank[sorted[0]] = k;
    for (int i = 1; i < sorted.size(); ++i) {
      if (sorted[i] != sorted[i - 1]) {
        rank[sorted[i]] = ++k;
      }
    }

    auto push = [&rank](std::vector<int>& arr, FenwickTree& ft, int val) {
      arr.push_back(val);
      ft.update(rank[val], 1);
    };

    FenwickTree ft1(rank.size());
    std::vector<int> arr1;
    arr1.reserve(n);
    push(arr1, ft1, nums[0]);

    FenwickTree ft2(rank.size());
    std::vector<int> arr2;
    arr2.reserve(n);
    push(arr2, ft2, nums[1]);

    const int maxRank = rank[sorted.back()];
    for (int i = 2; i < n; ++i) {
      int idx = rank[nums[i]];

      int greaterCount1 = ft1.query(idx + 1, maxRank);
      int greaterCount2 = ft2.query(idx + 1, maxRank);

      if (greaterCount1 > greaterCount2) {
        push(arr1, ft1, nums[i]);
      } else if (greaterCount1 < greaterCount2) {
        push(arr2, ft2, nums[i]);
      } else {
        if (arr1.size() <= arr2.size()) {
          push(arr1, ft1, nums[i]);
        } else {
          push(arr2, ft2, nums[i]);
        }
      }
    }

    for (int i = 0; i < arr1.size(); ++i) {
      nums[i] = arr1[i];
    }

    for (int i = 0; i < arr2.size(); ++i) {
      nums[i + arr1.size()] = arr2[i];
    }
    return nums;
  }
};
