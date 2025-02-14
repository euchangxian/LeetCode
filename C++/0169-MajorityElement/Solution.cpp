#include <cstddef>
#include <vector>

class Solution {
 public:
  int majorityElement(std::vector<int>& nums) {
    // Boyer-Moore Voting Algorithm
    // Finds the majority element in an array. A majority element is an element
    // which occurs more than floor(n/2) times.
    //
    // Intuitively, if a majority element exists, its occurence will be more
    // than the COMBINED occurences of all other elements.
    //
    // As we iterate through, we maintain a count of the majority element.
    // The majority element will contribute positively to the count, while
    // other elements will contribute negatively.
    // Owing to the property of the majority element, overall count will always
    // be positive.
    //
    // In the simplest of cases, consider the array:
    // [1, 1, 2]
    // iter 0: element = 1, count += 1 = 1
    // iter 1: element = 1, count += 1 = 2
    // iter 2: element = 2, count -= 1 = 1
    //
    // The algorithm finds the majority element for each prefix of the array:
    // nums[:1] = [1]           -> majority = 1, votes = 1
    // nums[:2] = [1, 1]        -> majority = 1, votes = 2
    // nums[:3] = [1, 1, 2]     -> majority = 1, votes = 1
    //
    // If we extend this to a longer array:
    // nums[:1] = [1]           -> majority = 1, votes = 1
    // nums[:2] = [1, 2]        -> majority = 1, votes = 0, change majority to 2
    // nums[:3] = [1, 2, 2]     -> majority = 2, votes = 1
    // nums[:4] = [1, 2, 2, 1]  -> majority = 2, votes = 0, change majority to 1
    // nums[:5] = [1, 2, 2, 1, 1] -> majority = 1, votes = 1
    // nums[:6] = [1, 2, 2, 1, 1, 1] -> majority = 1, votes = 2
    //
    // At each step, we're finding the majority element of the current prefix.
    // If the votes become 0, it means the current prefix doesn't have a clear
    // majority, so we reset with the next element.
    //
    // This example illustrates several key points:
    // 1. The majority can change as we progress through the array.
    // 2. When votes reach 0, we reset with the next element as the new
    //    candidate.
    // 3. The true majority element (1 in this case) may not be identified until
    //    later in the array.
    // 4. Even though 2 was the majority in some prefixes, 1 overtakes it by the
    // end due to its higher overall frequency.
    //
    // The key insight is that the majority element of the entire array will
    // eventually overtake any local majorities in prefixes. Even if it's
    // temporarily overtaken in some prefixes, it will regain the majority
    // by the end of the array due to its overall frequency.
    int majority;  // no need to initialize
    int votes = 0;
    for (const int num : nums) {
      if (votes == 0) {
        majority = num;
      }

      votes += (majority == num ? 1 : -1);
    }
    return majority;
  }
};
