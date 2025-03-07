#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <vector>

using i64 = long long;

// NOTE: Not working.
// 'constexpr' evaluation operation count exceeds limit of 33554432 (BitSet)
// 'constexpr' loop iteration count exceeds limit of 262144 (Array<bool>)
// constexpr std::size_t MAX_N{1'000'000};
// template <std::size_t N>
// consteval std::size_t countPrimes() {
//   if (N <= 1) {
//     return 0;
//   }
//
//   // Store only odd numbers.
//   // prime[i] represents the number 2*i + 1
//   std::array<bool, N / 2 + 1> prime{};
//   for (std::size_t i = 1; i <= N / 2; ++i) {
//     prime[i] = true;
//   }
//
//   // 2 is the first prime.
//   std::size_t count = 1;
//
//   for (std::size_t i = 1; i <= N / 2; ++i) {
//     if (prime[i]) {
//       ++count;
//
//       std::size_t num = 2 * i + 1;
//       if (static_cast<i64>(num) * num <= N) {
//         for (std::size_t j = num * num; j <= N; j += 2 * num) {
//           prime[j / 2] = false;
//         }
//       }
//     }
//   }
//
//   return count;
// }
// constexpr std::size_t NUM_PRIMES{countPrimes<MAX_N>()};

class Solution {
 public:
  std::vector<int> closestPrimes(int left, int right) {
    // Given [l, r], find two integers x, y within the range such that:
    // - x < y
    // - x and y are prime
    // - y - x is the minimum diff among all pairs satisfying the above.
    // Sieve up to r.
    // Then iterate starting from l, find first two primes.
    // As usual, runtime computation is easy: just need a linear sieve + search.
    // We can do compile time + binary search.
    // AHHHH. No. The first two primes in the range may not have the minimum
    // difference. Seems like a linear search is necessary.
    std::vector<int> primes;
    primes.reserve(80'000);  // < 78,000 with 10e6

    std::vector<bool> isPrime(right + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; static_cast<i64>(i) * i <= right; ++i) {
      if (isPrime[i]) {
        for (int j = i * i; j <= right; j += i) {
          isPrime[j] = false;
        }
      }
    }

    for (int i = 2; i <= right; ++i) {
      if (isPrime[i]) {
        primes.push_back(i);
      }
    }

    auto lower = std::lower_bound(primes.begin(), primes.end(), left);
    auto upper = std::upper_bound(lower, primes.end(), right);
    if (std::distance(lower, upper) < 2) {
      return {-1, -1};
    }

    std::vector<int> best{-1, -1};
    int minDiff = INT_MAX;
    for (auto it = lower; it != upper - 1; ++it) {
      int diff = *(it + 1) - *it;
      if (diff < minDiff) {
        minDiff = diff;
        best[0] = *it;
        best[1] = *(it + 1);
      }
    }
    return best;
  }
};
