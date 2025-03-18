#include <string>

class Solution {
 public:
  std::string fractionAddition(std::string expression) {
    int n = expression.length();

    // Running result;
    int numerator = 0;
    int denominator = 1;

    int i = 0;
    while (i < n) {
      int currNumerator = 0;
      int currDenominator = 0;

      // Parse the fraction
      bool isNegative = false;  // first '+' is omitted
      if (expression[i] == '+' || expression[i] == '-') {
        isNegative = expression[i] == '-';
        ++i;
      }

      while (std::isdigit(expression[i])) {
        currNumerator = (currNumerator * 10) + (expression[i] - '0');
        ++i;
      }

      currNumerator = isNegative ? -currNumerator : currNumerator;

      // Skip '/'
      ++i;

      while (std::isdigit(expression[i])) {
        currDenominator = (currDenominator * 10) + (expression[i] - '0');
        ++i;
      }

      // Add fractions together
      numerator = (numerator * currDenominator) + (currNumerator * denominator);
      denominator = denominator * currDenominator;
    }

    // Reduce the fractions, using their GCD
    int gcd = std::abs(euclidsGCD(numerator, denominator));

    numerator /= gcd;
    denominator /= gcd;
    return std::to_string(numerator) + '/' + std::to_string(denominator);
  }

 private:
  int euclidsGCD(int a, int b) {
    if (b == 0) {
      // if remainder is 0, return a which is the GCD
      return a;
    }

    return euclidsGCD(b, a % b);
  }
};
