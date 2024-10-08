#include <climits>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;

  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  vector<int> nodesBetweenCriticalPoints(ListNode* head) {
    // minDistance, maxDistance
    // minDistance will be the minimum of the distances between adjacent
    // critical points
    // maxDistance will be the distance between the left-most and the right-most
    // critical points
    vector<int> result = {INT_MAX, -1};

    int firstCriticalIndex = -1;
    int prevCriticalIndex = -1;

    ListNode* prev = head;
    ListNode* iter = head->next;
    int i = 1;
    while (iter != nullptr && iter->next != nullptr) {
      // Check if its a critical node
      if (prev->val < iter->val && iter->val > iter->next->val ||
          prev->val > iter->val && iter->val < iter->next->val) {
        // check if there was a first/prevCriticalIndex
        if (firstCriticalIndex == -1) {
          firstCriticalIndex = i;
        }

        // if there was a prevCriticalNode, then check minDistance
        if (prevCriticalIndex != -1) {
          result[0] = min(result[0], i - prevCriticalIndex);
        }
        prevCriticalIndex = i;
      }

      ++i;
      prev = iter;
      iter = iter->next;
    }

    if (result[0] == INT_MAX) {
      return {-1, -1};
    }

    result[1] = prevCriticalIndex - firstCriticalIndex;
    return result;
  }
};
