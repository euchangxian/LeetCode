#include <algorithm>
#include <bitset>
#include <ranges>
#include <stack>
#include <utility>
#include <vector>

constexpr int MOD = 1e9 + 7;
constexpr int MAX_N = 1e5;

std::vector<int> primes = []() {
  std::vector<int> primes;

  std::bitset<MAX_N + 1> isPrime;
  isPrime.flip();
  isPrime[0] = isPrime[1] = false;

  for (int i = 2; static_cast<long long>(i) * i <= MAX_N; ++i) {
    if (isPrime[i]) {
      primes.push_back(i);
      for (int j = i * i; j <= MAX_N; j += i) {
        isPrime[j] = false;
      }
    }
  }
  return primes;
}();

int countDistinctPF(int n) {
  int count = 0;
  for (int p : primes) {
    if (static_cast<long long>(p) * p > n) {
      break;
    }

    if (n % p == 0) {
      ++count;
      while (n % p == 0) {
        n /= p;
      }
    }
  }

  if (n > 1) {
    ++count;
  }
  return count;
}

int modMult(int a, int b) {
  return (static_cast<long long>(a) * b) % MOD;
}

int modPow(int n, int exponent) {
  int result = 1;
  int base = n;
  while (exponent > 0) {
    if (exponent & 1) {
      result = modMult(result, base);
    }
    base = modMult(base, base);
    exponent >>= 1;
  }

  return result;
}

class Solution {
 public:
  int maximumScore(std::vector<int>& nums, int k) {
    // Start with score of 1.
    // - Choose any non-empty subarray nums[l..r] not yet chosen (i.e,. each
    //   combination of (l, r) can be chosen only once
    // - Choose an element x in the subarray with the highest prime score.
    //   If there is multiple, choose the lowest index.
    // - Multiply score by x.
    // Prime Score of x is the number of distinct prime factors of x.
    // Return the maximum possible score after applying at most k operations.
    //
    // Suppose the Prime Scores are in Descending order.
    // Then, the optimal way would be to choose n subarrays for the first,
    // n-1 for the second, n-2 for the third...
    // etc, summing up to n(n+1)/2, which happens to be the constraint of k.
    // Is this optimal.
    //
    // But making it more complicated, we must choose the highest prime score
    // in the unsorted subarray, making it difficult to cleanly perform ops?
    // If the element is in the middle, then take all the subarrays starting
    // with it, ending with it.
    // The issue comes when an arbitrary element with a lower prime score needs
    // to be selected? Including the larger prime scores will cause the other
    // element to be chosen instead (also repeated choice).
    // Not so straightforward.
    //
    // Ah. We also want to choose the higher x as much as possible. Consider
    // the trivial case
    // nums = {1e9+7, 10, 12}.
    // Both 10 and 12 have a higher prime score of 2, as compared to our
    // prime 1e9 + 7, which has a prime score of 1.
    // But clearly, multiplying by 1e9+7 will give us a larger score, even if
    // done only once.
    // Just that the upper_bound on the number of times 1e9+7 can be chosen
    // is 1 (l, r) = (0, 0). Expanding rightwards will chose 10 with a prime
    // score of 2 instead.
    //
    // Thus, we want to sort by nums[i] in descending order. Greedily pick the
    // upper_bound.
    // This upper bound can be computed by?
    // Feels like the number of subarrays within (l, r), where l, r is the
    // largest subarray in which x has the largest prime score.
    // e.g., numSubarrays = (i-l) * (r-i) (nCr)
    // Interesting subproblems.
    const int n = nums.size();
    std::vector<int> primeScore =
        nums | std::ranges::views::transform(countDistinctPF) |
        std::ranges::to<std::vector>();

    // find left[i] and right[i] such that
    // - left[i] represents j < i such that primeScore[j] > primeScore[i],
    // - right[i] represents k > i such that primeScore[k] > primeScore[i].
    // Use a monotonically non-increasing stack for left[i],
    //                     decreasing stack for right[i]
    std::vector<int> left(n), right(n);
    std::stack<int> s;
    for (int i = 0; i < n; ++i) {
      while (!s.empty() && primeScore[s.top()] < primeScore[i]) {
        s.pop();
      }
      left[i] = s.empty() ? -1 : s.top();
      s.push(i);
    }

    s = {};
    for (int i = n - 1; i >= 0; --i) {
      // NOTE: we use <= here to respect the "leftmost" i constraint,
      // given that we are iterating right-to-left.
      while (!s.empty() && primeScore[s.top()] <= primeScore[i]) {
        s.pop();
      }
      right[i] = s.empty() ? n : s.top();
      s.push(i);
    }

    std::vector<std::pair<int, int>> sorted;
    sorted.reserve(n);
    for (int i = 0; i < nums.size(); ++i) {
      sorted.emplace_back(nums[i], i);
    }
    std::sort(sorted.begin(), sorted.end(), [](const auto& p1, const auto& p2) {
      // tie-break by left-most i.
      return p1.first > p2.first ||
             (p1.first == p2.first && p1.second < p2.second);
    });

    int score = 1;
    for (const auto [x, i] : sorted) {
      long long repeats =
          std::min(static_cast<long long>(k),
                   static_cast<long long>(i - left[i]) * (right[i] - i));
      k -= repeats;

      // score = score * x^repeats
      score = modMult(score, modPow(x, repeats));
    }
    return score;
  }
};
