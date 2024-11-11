#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <vector>

constexpr bool isPrime(int n) {
  if (n <= 1) {
    return false;
  }

  if (n <= 3) {
    return true;
  }

  // slight optimization to isPrime.
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }

  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

template <std::size_t N>
constexpr std::array<int, N> generatePrimes() {
  std::array<int, N> primes{};

  int count = 0;
  int num = 2;
  while (count < N) {
    if (isPrime(num)) {
      primes[count++] = num;
    }
    ++num;
  }
  return primes;
}

// The 168th prime is 997, 169th prime is 1009. Therefore, 169 is sufficient.
static constexpr std::array<int, 169> primes = generatePrimes<169>();

class Solution {
 private:
 public:
  bool primeSubOperation(std::vector<int>& nums) {
    // Pick an index i not yet picked, pick a prime p strictly less than nums[i]
    // then subtract p from nums[i].
    // Return true if nums can be made a strictly increasing array with any
    // number of operations.
    // Hmm. 1 is not a prime.
    // Also, we want to pick p such that nums[i] is minimized, while still being
    // greater than nums[i-1].
    // Simulation? Just iterate through and greedily pick.
    // Given the list of prime numbers, we want to find a prime p such that
    // nums[i-1] < nums[i] - p
    // Rewriting the equation, to find p
    // p < nums[i] - nums[i-1] ---> use std::lower_bound to
    // find nums[i] - nums[i-1], then take the previous element.
    int prev = 0;
    for (int i = 0; i < nums.size(); ++i) {
      int limit = nums[i] - prev;

      if (limit < 0) {
        // indicates nums[i] is already <= prev, minusing further would not
        // increase nums[i] such that nums[i-1] < nums[i]
        return false;
      }

      auto primeIt = std::lower_bound(primes.begin(), primes.end(), limit);
      if (primeIt != primes.begin()) {
        nums[i] -= *(--primeIt);
      }

      // May or may not have updated nums[i]. If a prime number p does not
      // exist, AND that the current number is smaller than the previous, then
      // return false; we cannot make it increasing.
      if (nums[i] <= prev) {
        return false;
      }

      prev = nums[i];
    }

    // reaching here means the array can be made strictly increasing.
    return true;
  }
};
