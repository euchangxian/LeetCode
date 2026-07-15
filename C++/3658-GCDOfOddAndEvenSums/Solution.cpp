class Solution {
 public:
  int gcdOfOddEvenSums(int n) {
    // Return gcd(sumOdd, sumEven)
    // - sumOdd: sum of smallest n positive odd numbers.
    // - sumEven: sum of smallest n positive even numbers
    //
    // sumOdd  = 1 + 3 + ... + (2n-1) = n^2.
    // sumEven = 2 + 4 + ... + 2n     = n(n+1)
    // => gcd = n
    return n;
  }
};
