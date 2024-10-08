#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

constexpr size_t NUM_ALPHA = 26;

class Solution {
 public:
  int findTheLongestSubstring(string s) {
    // The intuition to this problem is the parity of the vowels.
    // Consider two indices i and j, i < j, s[i] == s[j].
    // i.e., WLOG, the vowel 'a' is at index i and index j.
    // Consider the parity of the vowels.
    // If the parity of the masks at index i and index j are equal,
    // then we found a new valid substring, since odd - odd = even,
    // even - even = even.
    // Otherwise, we can record the parity of the mask and the corresponding
    // index, in case there are future parities which match.
    array<size_t, NUM_ALPHA> shiftIdx{};
    shiftIdx['a' - 'a'] = 1;
    shiftIdx['e' - 'a'] = 2;
    shiftIdx['i' - 'a'] = 3;
    shiftIdx['o' - 'a'] = 4;
    shiftIdx['u' - 'a'] = 5;

    // 2^(NUM_VOWELS). All possible parities. Avoid using hashmaps/sets
    // stores the index of the first seen parity.
    // Store 1-indexed positions
    array<int, 64> parity{};
    parity.fill(-1);  // -1 indicate not seen. Could use a map/seen array

    // Reads from reverse, where the MSB is at the end, i.e. uoiea
    // upper 3 bits not shown, since only 5 bits for each vowels is needed
    // Mask represents the parity of the vowels. 0 represents even parity,
    // 1 represents odd parity.
    uint8_t curr = 0;  // 00000
    parity[curr] = 0;  // handle the case where the entire string is valid.
    int longest = 0;
    for (int i = 0; i < s.length(); ++i) {
      // shiftIdx is 0 for non-vowels. This causes the vowelBit to shift left
      // by 0 bits, which causes the 1 to shift right into a zero
      // For vowels, the 1-indexed shiftIdx will be adjusted to 0-indexed
      // by the right shift giving the correct parity bit.
      uint8_t vowelBit = 1 << shiftIdx[s[i] - 'a'] >> 1;
      curr ^= vowelBit;
      if (parity[curr] == -1) {
        parity[curr] = i + 1;  // store 1-indexed
      }

      longest = max(longest, i + 1 - parity[curr]);
    }

    return longest;
  }
};
