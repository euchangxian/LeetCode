#ifdef LOCAL
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
#endif  // LOCAL

class Solution {
 public:
  bool hasCycle(ListNode* head) {
    if (!head) {
      return false;
    }

    ListNode* slow = head;
    ListNode* fast = head;

    // Until fast reaches the end of the list,
    // or if there is a cycle and they intersect
    while (fast->next && fast->next->next) {
      slow = slow->next;
      fast = fast->next->next;

      if (slow == fast) {
        return true;
      }
    }
    return false;
  }
};
