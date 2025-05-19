#include <algorithm>
#include <string>
#include <vector>

class Solution {
 public:
  std::string triangleType(std::vector<int>& nums) {
    // nums of size 3. Return "equilateral"|"isosceles"|"scalene"|"none", if
    // all sides are equal, two sides are equal, all different, or not triangle.
    //
    // Forgot how to test for NOT triangle. Triangle inequality or something,
    // a + b > c must be satisfied.

    // inverse these commented conditions
    // if (a + b > c && b + c > a && a + c > b) {
    // if (std::abs(a - b) < c && c < a + b) {
    // if (int longest = std::max({a, b, c}); longest < a + b + c - longest) {
    int a = nums[0], b = nums[1], c = nums[2];
    if (int longest = std::max({a, b, c}); 2 * longest >= a + b + c) {
      return "none";
    }

    if (a == b && b == c) {
      return "equilateral";
    }
    if (a == b || b == c || a == c) {
      return "isosceles";
    }
    return "scalene";
  }
};
