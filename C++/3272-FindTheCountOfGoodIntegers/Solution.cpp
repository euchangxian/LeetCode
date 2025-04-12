#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>

using i64 = long long;

constexpr std::array<i64, 11> fact = []() {
  std::array<i64, 11> fact{};
  fact[0] = 1;
  for (int i = 1; i < fact.size(); ++i) {
    fact[i] = i * fact[i - 1];
  }
  return fact;
}();

class Solution {
 public:
  i64 countGoodIntegers(int n, int k) {
    // An integer x is called k-palindromic if:
    // - x is a palindrome, and
    // - x is divisible by k.
    // An integer is called good if its digits can be rearranged to form a
    // k-palindromic integer.
    // Return the number of Good Integers containing n digits.
    //
    // Doesnt seem like DP. At least there is no obvious element of choice.
    // Note the extremely small constraints 1 <= n <= 10 and 1 <= k <= 9
    // Also, recall there is some number theory for divisible by K, involving
    // sums, last digits, sum of digits, etc...
    // i.e., k=2 => last digit must be even.
    //       k=3 => sum of digits divisible by 3
    //       k=4 => decimal representation of last 2 digits is divisible by 4
    //       k=5 => last digit is 0 or 5
    //       k=6 => divisible by 2 and 3
    //       k=7 => remove last digit d, subtract 2*d, repeat until 0 or a
    //              number divisible by 7 is obtained.
    //       k=8 => decimal representation of last 3 digits is divisible by 8
    //       k=9 => sum of digits is divisible by 9
    //
    // Without this, seems like enumerating all n-digit permutations is
    // necessary to check for divisibility (while pruning non-palindromes).
    // Suppose n is even, then every digit must occur an even number of times.
    // If n is odd, then exactly one character must have an odd number of
    // occurence, and placed in the centre.
    //
    // At the same time, not necessary to actually do a complete search? Can
    // we use combinatorics/permutations?
    // Hm. Notice that we have the re-arrangement operation. This means that
    // once we find a k-palindromic number, we can obtain all other
    // permutations.
    // The digit frequencies can be cached to avoid repeated computation?
    //
    // 1. Enumerate all possible n-length palindromes. This is 10^5 at most.
    //   a. At the same time, if the palindrome is k-palindromic, store it for
    //      later processing (in a set)
    // 2. Count permutations. n!/a!...c!, i.e., fact(len) / fact(occurences[i])
    std::string digits(n, '0');
    std::unordered_set<std::string> good;
    good.reserve(1e5);  // prevent resize + rehash as much as possible.
    dfs(n, k, good, digits, 0);

    i64 total = 0;
    for (std::string_view s : good) {
      std::array<int, 10> freq{};
      for (char c : s) {
        ++freq[c - '0'];
      }

      // WARNING: zeros cannot be appended/rearranged to the leading positions.
      // Thus, we have (n-freq[0]) choices for the first position, and therefore
      // (n-1)! arrangements for the remaining positions.
      i64 count = (n - freq[0]) * fact[n - 1];
      for (int occ : freq) {
        count /= fact[occ];
      }

      total += count;
    }
    return total;
  }

 private:
  void dfs(int n,
           int k,
           std::unordered_set<std::string>& good,
           std::string& digits,
           int i) {
    if (i >= (n + 1) / 2) {
      i64 num = std::stoll(digits);

      if (num % k == 0) {
        std::string copy = digits;
        std::sort(copy.begin(), copy.end());
        good.emplace(std::move(copy));
      }
      return;
    }

    for (char d = '0'; d <= '9'; ++d) {
      if (d == '0' && i == 0) {
        continue;  // avoid leading 0s
      }

      digits[i] = digits[n - 1 - i] = d;
      dfs(n, k, good, digits, i + 1);
      // no need to 'backtrack' i.e., save original digit, and set back.
    }
  }
};
