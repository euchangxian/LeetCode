#include <array>
#include <functional>
#include <numeric>
#include <vector>

using i64 = long long;
constexpr int BITS = 32;

class Solution {
 public:
  int getXORSum(std::vector<int>& arr1, std::vector<int>& arr2) {
    // Lol. XOR and AND is distributive
    // That means we can just do XOR(arr1) AND XOR(arr2)
    // (arr1[i] & arr2[1]) ^ (arr1[i] & arr2[2]) ...
    // arr1[i] & (arr2[1] ^ arr2[2] ^ ...)
    return std::reduce(arr1.begin(), arr1.end(), 0, std::bit_xor<>{}) &
           std::reduce(arr2.begin(), arr2.end(), 0, std::bit_xor<>{});
  }

  int getXORSumNaive(std::vector<int>& arr1, std::vector<int>& arr2) {
    // Given arr1 and arr2 of non-negative integers.
    // Consider arr3 = {arr1[i] AND arr2[j] for all (i, j)}
    // Return the XOR sum of arr3.
    //
    // With constraints, enumerating all pairs in O(N^2) to get arr3 will TLE.
    // AND is monotonically non-increasing.
    // In terms of bits, consider arr1[i].
    // Then, consider arr2. We can count the frequency of each bit's occurence,
    // which determines how many times a certain bit would appear.
    // Should be about there.
    // Two O(N) passes over arr1 and arr2 to get the frequency of each bit's
    // occurences.
    // To get the final occurences, multiply the count.
    // Then XOR, which is setting even frequency bits to 0, and odd to 1.
    //
    // 001,010,011 => freq1={0,2,2}
    // 110,101     => freq2={2,1,1}
    //                final={0,2,2}
    //                  xor={0,0,0}=0
    //
    // 1100 => freq1={1,1,0,0}
    // 0100 => freq2={0,1,0,0}
    //         final={0,1,0,0}
    //           xor={0,1,0,0}=4
    std::array<int, BITS> freq1{}, freq2{};
    auto addFreq = [](std::array<int, BITS>& freq, int n) {
      while (n) {
        int idx = __builtin_ctz(n);
        ++freq[idx];
        n &= (n - 1);
      }
    };

    for (int num : arr1) {
      addFreq(freq1, num);
    }
    for (int num : arr2) {
      addFreq(freq2, num);
    }

    int final = 0;
    for (int i = 0; i < BITS; ++i) {
      i64 count = 1LL * freq1[i] * freq2[i];
      if (count & 1LL) {
        final += (1 << i);
      }
    }
    return final;
  }
};
