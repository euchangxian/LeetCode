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
  int getDecimalValue(ListNode* head, int result = 0) {
    // Value of each node is either 0 or 1, where the linked list represent
    // the number in binary.
    // The MSB is at the head.
    if (!head) {
      return result;
    }
    return getDecimalValue(head->next, 2 * result + head->val);
  }
};
