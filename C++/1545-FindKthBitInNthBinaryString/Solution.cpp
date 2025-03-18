#include <algorithm>
#include <cstddef>
#include <string>

class Solution {
 private:
  std::string invert(std::string str) {
    for (std::size_t i = 0; i < str.length(); ++i) {
      str[i] = (1 - (str[i] - '0')) + '0';
    }
    return str;
  }

  std::string findNthString(int n) {
    if (n <= 1) {
      return "0";
    }

    std::string prevString = findNthString(n - 1);

    std::string inverted = invert(prevString);
    reverse(inverted.begin(), inverted.end());

    return prevString + '1' + inverted;
  }

 public:
  // Recursive, similar to binary searching.
  char findKthBit(int n, int k) {
    if (n == 1) {
      return '0';
    }

    // len(S1) = 1
    // len(S2) = 2 * len(S1) + 1
    // len(S3) = 2 * len(S2) + 1
    int nthStrLength = (1 << n) - 1;  // 2^n - 1

    // Rules of the string construction means that if k is in the middle, then
    // the kth bit must be '1'
    // Ceiling division, since k is 1-indexed.
    int mid = ((nthStrLength + 1) / 2);
    if (k == mid) {
      return '1';
    }

    // Otherwise, recurse on the appropriate half
    if (k < mid) {
      return findKthBit(n - 1, k);
    }

    // Bits in the second half are reversed. Thus, adjust k accordingly instead
    // of (k - mid), do (len - k + 1), where the + 1 arises from the fact that
    // k needs to be 1-indexed.
    char invertedKthBit = findKthBit(n - 1, nthStrLength - k + 1);

    // The bits in the second halve are inverted.
    return (1 - (invertedKthBit - '0')) + '0';
  }

  // Simulation
  char findKthBitNaive(int n, int k) {
    std::string nthString = findNthString(n);
    return nthString[k - 1];
  }
};
