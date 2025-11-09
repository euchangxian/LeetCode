class Solution {
 public:
  int countOperations(int num1, int num2) {
    // given two non-negative integers.
    // In one operation,
    // - if num1 >= num2, subtract num2 from num1. num1 -= num2
    // - else, subtract num1 from nums2. num2 -= num1
    // Return the number of operations required to make either 0.
    //
    // Simulation?
    // Can we do better?
    // Isn't this Euclid's GCD? Lol.
    if (num1 == 0 || num2 == 0) {
      return 0;
    }

    return (num1 / num2) + countOperations(num2, num1 % num2);
  }
};
