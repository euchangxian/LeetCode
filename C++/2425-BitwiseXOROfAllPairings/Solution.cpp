#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  int xorAllNums(std::vector<int>& nums1, std::vector<int>& nums2) {
    // nums3 contains the bitwise XOR of all pairings between nums1 and nums2,
    // i.e., for all x in nums1:
    //         for all y in nums2:
    //             => x ^ y in nums3
    // Want: bitwise XOR of all integers in nums3.
    //
    // Firstly, brute-force n^2 is not possible due to constraints. And
    // obviously there would be a better way.
    // Notice that we want the resulting XOR. Thus, the result would look
    // something like:
    // ... (x1 ^ y1) ^ (x1 ^ y2) ^ ... ^ (x1 ^ yn)
    // Thus, each xi will be XOR-ed with itself nums2.size times.
    // Then, we intuitively know that its a parity problem, since the
    // corresponding yi will be XOR-ed with itself nums1.size times.
    //
    // Since XOR is commutative, we can freely rearrange the equation.
    // Let nums1.size be n1, nums2.size be n2.
    // Then:
    // result = (xi ^ xi ^ ...) ^ (yi ^ yi ^ ... yi)
    //
    // If n is even, then x^x = 0. Otherwise, x^x^x = x.
    const int n1 = nums1.size();
    const int n2 = nums2.size();

    int result = 0;
    if (n2 & 1) {
      for (int x : nums1) {
        result ^= x;
      }
    }

    if (n1 & 1) {
      for (int y : nums2) {
        result ^= y;
      }
    }

    return result;
  }
};
