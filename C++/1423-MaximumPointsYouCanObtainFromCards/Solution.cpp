#include <algorithm>
#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  int maxScore(std::vector<int>& cardPoints, int k) {
    // Naively, seems like 2^k backtracking, i.e., choose to take from front or
    // back for a total of k elements.
    // Can we do better?
    // Probably would be to maintain two states i.e., leftIdx, rightIdx,
    // memoizing the maximum points.
    // Lol. Saw the question tags. DP is not necessary.
    //
    // Note that an earlier decision affects the outcome of later decisions.
    // i.e., to take the 2nd card from the front, the first card must be taken
    // first.
    // Hm. This does seem like DP.
    // HM... What if we reduce this to a sliding window! Note that we want a
    // window of size k!
    // By taking all left elements, we have a window of size k
    // For each right element that we want to take, we remove the rightmost
    // element of the window, and take the element from the right.
    // By doing this, we have effectively reduced this problem to
    // "Given an array nums, find the subarray of size k with the largest sum,
    // that includes either the first and/or last element"

    // For conventions, where the window slides rightwards, start by taking all
    // cards from the right side.
    const size_t n = cardPoints.size();
    int start = n - k;
    int end = n - 1;

    int windowSum = 0;
    for (int i = start; i <= end; ++i) {
      windowSum += cardPoints[i];
    }

    int result = windowSum;
    for (int i = 0; i < k; ++i) {
      // Remove leftmost of window, add rightmost
      windowSum -= cardPoints[(++start) % n];
      windowSum += cardPoints[(++end) % n];
      result = std::max(result, windowSum);
    }

    return result;
  }
};
