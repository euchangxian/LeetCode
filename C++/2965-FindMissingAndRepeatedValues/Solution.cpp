#include <vector>

class Solution {
 public:
  std::vector<int> findMissingAndRepeatedValues(
      std::vector<std::vector<int>>& grid) {
    // n*n grid with values in the range [1..n^2].
    // a appears twice, b is missing.
    // IIRC this is a 2D variant of a question i've done before. Except there
    // isnt much difference in the approach. Oh not entirely the same.
    // See 260.Single Number III. Problem is similar, where SingleNumber3
    // involves every number occuring twice, and two numbers occuring only once.
    // O(N^2) space would trivialize this.
    //
    // Let's try constant space.
    // Taking the XOR sum of the index and the values (effectively reducing
    // the problem into some variant of Single Number 3, where we make every
    // number occur twice, b occur once, a occur thrice == once):
    // XORSum = (1^1) ^ (2^2) ^ ... ^ (b^a) (missing b, extra a)
    //        = a^b
    // Then, we can partition the numbers into two groups based on the set bits
    // in their XOR sum. (See Single Number 3 for the explanation)
    // This gives us a and b, BUT does not help us differentiate between the
    // two yet, which is necessary since we must return {a, b}.
    // A naive one would be to just iterate again (for a total of 3 passes) to
    // figure out the duplicate number (which will be one of the two numbers we
    // found).
    //
    // Nah, we can do better. For SingleNumber3, the range of values was
    // unbounded.
    // Here, we know the range [1..n^2].
    // By taking the expected sum: we have 1+2+...+ a +...+ b +...+n^2.
    // The actual sum would be 1+2+...+ a + a +... +n^2
    // Thus, by taking the difference actual - expected, we get a-b.
    // This, combined with the XOR Sum allows for two passes.
    // We can still do better.
    // Sum of Squares!
    // Expected: 1^2 + ... + a^2 + ... + b^2 + ...
    // Actual: 1^2 + ... + a^2 + a^2 + ...
    // actual - diff = a^2 - b^2 == (a+b)(a-b)
    // Thus, we can derive a+b and a-b, allowing us to solve for both a and b.
    using i64 = long long;
    const i64 n = grid.size();

    // or we can iterate and build up, especially for the square sum
    const i64 nSq = n * n;
    const i64 expectedSum = nSq * (nSq + 1) / 2;
    const i64 expectedSquareSum = nSq * (nSq + 1) * (2 * nSq + 1) / 6;
    i64 sum = 0;
    i64 squareSum = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        sum += grid[i][j];
        squareSum += static_cast<i64>(grid[i][j]) * grid[i][j];
      }
    }

    int aMinusB = sum - expectedSum;
    int aSqMinusBSq = squareSum - expectedSquareSum;
    int aPlusB = aSqMinusBSq / aMinusB;

    int twoA = aPlusB + aMinusB;
    int a = twoA / 2;
    int b = aPlusB - a;
    return {a, b};
  }
};
