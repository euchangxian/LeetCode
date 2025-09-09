#include <algorithm>
#include <array>
#include <deque>
#include <utility>

constexpr int MAX_N = 1000;
constexpr int MOD = 1E9 + 7;
constexpr auto modAdd = [](long long x, long long y) {
  return ((x + y) % MOD + MOD) % MOD;
};

class Solution {
 public:
  int peopleAwareOfSecret(int n, int delay, int forget) {
    std::array<int, MAX_N + 1> dp{};
    dp[1] = 1;
    long long result = 0;
    long long share = 0;
    for (int i = 2; i <= n; ++i) {
      share = modAdd(share,
                     dp[std::max(i - delay, 0)] - dp[std::max(i - forget, 0)]);
      dp[i] = share;
    }
    for (int i = n - forget + 1; i <= n; ++i) {
      result = modAdd(result, dp[i]);
    }

    return result;
  }

  int peopleAwareOfSecretSimulation(int n, int delay, int forget) {
    // day 1, one person knows a secret.
    // After delay day, each person who knows a secret will share the
    // secret with someone who does not know.
    // After forget days of knowing the secret, they will forget the secret.
    // Return number of people who knows the secret at the end of day n.
    //
    // Each person can share the secret for/to (forget - delay) days == people.
    // This takes a total of forget days.
    // Simulation is okay with these constraints.
    // But it gets difficult to track who is expiring/forgetting.
    // Deque?
    // number of people that knows.
    long long canShare = 0;
    long long result = 1;

    std::deque<std::pair<int, long long>> areSharing;
    areSharing.emplace_back(1 + delay, 1);

    std::deque<std::pair<int, long long>> willForget;
    willForget.emplace_back(1 + forget, 1);

    for (int day = 2; day <= n; ++day) {
      while (!areSharing.empty() && areSharing.front().first <= day) {
        canShare = modAdd(canShare, areSharing.front().second);
        areSharing.pop_front();
      }

      while (!willForget.empty() && willForget.front().first <= day) {
        long long forgettingCount = willForget.front().second;
        willForget.pop_front();

        canShare = modAdd(canShare, -forgettingCount);
        result = modAdd(result, -forgettingCount);
      }

      long long newPeopleToday = canShare;
      if (newPeopleToday > 0) {
        result = modAdd(result, newPeopleToday);
        areSharing.emplace_back(day + delay, newPeopleToday);
        willForget.emplace_back(day + forget, newPeopleToday);
      }
    }

    return result;
  }
};
