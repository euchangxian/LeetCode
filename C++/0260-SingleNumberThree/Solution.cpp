#include <vector>

using namespace std;
class Solution {
public:
  // Find the two numbers that appear exactly once in the array. Would be
  // simple, but the constraints are to use constant extra space.
  // Using XOR properties where a XOR a = 0, and 0 XOR b = b, we can easily find
  // the XOR of the two numbers that appear only once.
  //
  // a XOR a = 0, (a XOR a) XOR b = b, ((a XOR a) XOR b) XOR c = b XOR c
  //
  // The difficulty lies in extracting both b and c. If we know one, we can
  // extract the other, since (b XOR c) XOR b = c
  vector<int> singleNumber(vector<int> &nums) {
    int totalXOR = 0;
    for (int num : nums) {
      totalXOR ^= num;
    }

    // TODO internalize this...
    //  1,   2,   1,   3,   2,   5
    // 001, 010, 001, 011, 010, 101
    // totalXOR = 6  = 110
    // Looking at the bits, starting from the LSB,
    // the first "set" bit is the 2nd-last/middle bit 1 '1' 0,
    // The unique property arising from knowing this is that we can
    // partition the array into two distinct groups, numbers that
    // have the corresponding bit as '0', and numbers that have it as '1'.
    // Since the non-single numbers in either groups will cancel themselves
    // out, we can extract the single numbers.
    unsigned int leastSignificantSetBit = totalXOR & -(unsigned int)totalXOR;

    vector<int> singleNumbers = vector<int>(2, 0);
    for (int num : nums) {
      // find out which group the current number belong to
      int group = num & leastSignificantSetBit;
      if (group) {
        singleNumbers[1] ^= num;
      } else {
        singleNumbers[0] ^= num;
      }
    }
    return singleNumbers;
  }
};
