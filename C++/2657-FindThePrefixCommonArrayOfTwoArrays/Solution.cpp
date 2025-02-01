#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> findThePrefixCommonArray(std::vector<int>& A,
                                            std::vector<int>& B) {
    // A and B are integer permutations of length n, [1..n]
    // A prefix common array of A and B is C such that
    // C[i] == sum(intersect(A[0..i], B[0..i]))
    // Given n<=50, a bitmask would certainly work.
    // O(1) update, O(1) AND to check intersection.
    using i64 = long long;
    const int n = static_cast<int>(A.size());
    i64 inA = 0LL;
    i64 inB = 0LL;

    std::vector<int> prefixCommon(n);
    for (int i = 0; i < n; ++i) {
      inA = inA | (1LL << A[i]);
      inB = inB | (1LL << B[i]);

      prefixCommon[i] = __builtin_popcountll(inA & inB);
    }
    return prefixCommon;
  }
};
