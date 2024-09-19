#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
private:
  inline bool isNoZero(int n) {
    bool noZero = true;
    while (n > 0) {
      noZero = noZero && (n % 10);
      n /= 10;
    }
    return noZero;
  }

public:
  vector<int> getNoZeroIntegers(int n) {
    // Note some properties:
    // if the number is 10, then we want [1, 9]
    // if the number is 11, [1, 10] is not correct. we need [2, 9]
    // for any number between 2 and 9, every combination works.
    // Therefore, by exploiting this property, we can recursively process
    // each digit of n, reducing the runtime drastically to O(logn)
    int a = 0;
    int b = 0;

    // Keep track of which place we are processing: the ones, tens, hundredths
    int multiplier = 1;
    while (n > 0) {
      int digit = n % 10;
      n /= 10;

      if (digit == 0) {
        // n looks something like xx10 or x000
        a += 1 * multiplier;
        b += 9 * multiplier;

        // Can visualize this as borrowing from the next digit (which is ten
        // times bigger than the current. We are iterating from least
        // significant to most significant)
        // i.e., x00 (after dividing by 10) becomes y99
        // Or more concretely:
        // Start with 1 0 0
        // the right-most 0 can't really be splitted into 1 and 9.
        // Therefore, 'borrow' one from the next: 0 10 0 -> 0 9 10
        // Split 10 into 1 and 9: 0 9 10
        //                        0 9 1
        //                            9
        // Then for the next iteration: 0 9
        //                              0 1
        //                                8
        // 9 can be splitted simply into 1 and 8 without having to borrow
        --n;
      } else if (digit == 1 && n > 0) {
        a += 2 * multiplier;
        b += 9 * multiplier;

        --n; // Borrow '10' from next digit to get 11
      } else {
        a += 1 * multiplier;
        b += (digit - 1) * multiplier;
      }

      multiplier *= 10;
    }

    return {a, b};
  }

  vector<int> getNoZeroIntegersNaive(int n) {
    // No-Zero integers are integers without 0 in its decimal representation
    // Return [a, b] such that a and b are No-Zero and a + b = n
    // Guaranteed to have a valid answer.
    // Naively, two pointers, start at 1 and n - 1.
    // Worst case seems to be about 100+ iterations
    int start = 1;
    int end = n - 1;
    while (start <= end) {
      if (isNoZero(start) && isNoZero(end)) {
        return {start, end};
      }
      ++start;
      --end;
    }

    return {};
  }
};
