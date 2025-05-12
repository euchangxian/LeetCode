#include <array>
#include <ranges>
#include <vector>

class Solution {
 public:
  std::vector<int> findEvenNumbers(std::vector<int>& digits) {
    std::array<int, 10> freq{};
    for (int x : digits) {
      ++freq[x];
    }

    std::vector<int> answer;
    for (int hundredths = 1; hundredths <= 9; ++hundredths) {
      if (freq[hundredths] == 0) {
        continue;
      }
      --freq[hundredths];
      for (int tens = 0; tens <= 9; ++tens) {
        if (freq[tens] == 0) {
          continue;
        }
        --freq[tens];
        for (int ones = 0; ones <= 9; ones += 2) {
          if (freq[ones] == 0) {
            continue;
          }
          answer.push_back(hundredths * 100 + tens * 10 + ones);
        }
        ++freq[tens];
      }
      ++freq[hundredths];
    }
    return answer;
  }
  std::vector<int> findEvenNumbersLookup(std::vector<int>& digits) {
    // Given digits with duplicates, find all unique integers that follow
    // the requirements:
    // - the integer consist of the concatenation of three elements from digits
    //   in any arbitrary order.
    // - No leading zeroes
    // - Even.
    //
    // can do a reverse lookup.
    std::array<int, 10> freq{};
    for (int x : digits) {
      ++freq[x];
    }

    std::vector<int> answer;
    for (int i = 100; i < 1000; i += 2) {
      std::array<int, 10> curr{};
      int n = i;
      while (n) {
        int d = n % 10;

        ++curr[d];
        n /= 10;
      }

      bool valid = true;
      for (const auto [actual, expected] :
           std::ranges::views::zip(freq, curr)) {
        if (actual < expected) {
          valid = false;
          break;
        }
      }
      if (valid) {
        answer.push_back(i);
      }
    }
    return answer;
  }
};
