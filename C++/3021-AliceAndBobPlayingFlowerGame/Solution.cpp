using i64 = long long;

class Solution {
 public:
  i64 flowerGame(int n, int m) {
    // Two lanes of flowers with Alice and Bob on opposite sides.
    // x flowers in the first lane, y flowers in the second lane.
    // The game proceeds with Alice starting first.
    // In each turn:
    // - choose either lane and pick one flower from their side.
    // - at the end of the turn, if there are no flowers left, the current
    //   player captures their opponent and wins the game.
    // Given n, m - compute the number of possible pairs (x, y) that satisfy:
    // - Alice wins,
    // - Number of flowers in the first lane must be in the range [1..n]
    // - Number of flowers in the second lane must be in the range [1..m]
    //
    // First, how can we determine who wins efficiently, i.e., a closed-form
    // solution.
    // Given that Alice starts first, and one flower can be picked per turn:
    // Consider the parity of (x+y):
    // odd -> Alice wins
    // even -> Bob wins
    //
    // Starting from (1, 1):
    // #ways at (x, y) = #ways at (x-1, y) + (x, y-1) + (x-1, y-1)
    // dp[x][y] => O(N^2).
    // Too slow. How can we do better? We already know odd (x+y) gives us
    // the cases where Alice wins.
    // Odd+Even=Odd
    // Even+Odd=Odd
    // Technically, a step of 2 is sufficient to pass I believe.
    // Do we even have to iterate? Seems like a closed-form solution is possible
    // WLOG:
    // #odd in the range [1..x] * #even in the range [1..y]
    i64 numOddX = (n + 1) / 2;
    i64 numEvenX = n / 2;

    i64 numOddY = (m + 1) / 2;
    i64 numEvenY = m / 2;

    return (numOddX * numEvenY) + (numEvenX * numOddY);
  }
};
