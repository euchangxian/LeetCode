#include <utility>
#include <vector>

constexpr int MAX_N = 1e5;

// For sparse vectors, store the indices where vec[i] is non-zero.
// Thus, when taking the dot product of two vectors, only multiply where
// the indices match.
class SparseVector {
 public:
  SparseVector(std::vector<int>& nums) {
    // nonzero.reserve(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != 0) {
        nonzero.emplace_back(i, nums[i]);
      }
    }
  }

  // Return the dotProduct of two sparse vectors
  int dotProduct(SparseVector& vec) {
    // Given that both store the non-zero indices in ascending order,
    // we can efficiently check using two-ptr.
    int prod = 0;

    auto it1 = this->nonzero.begin();
    auto it2 = vec.nonzero.begin();
    while (it1 != this->nonzero.end() && it2 != vec.nonzero.end()) {
      if (it1->first == it2->first) {
        prod += it1->second * it2->second;
        ++it1;
        ++it2;
      } else if (it1->first < it2->first) {
        ++it1;
      } else {
        ++it2;
      }
    }
    return prod;
  }

 private:
  std::vector<std::pair<int, int>> nonzero;
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
