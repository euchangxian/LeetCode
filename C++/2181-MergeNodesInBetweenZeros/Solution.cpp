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
  ListNode* mergeSequence(ListNode* accumulator, ListNode* current) {
    if (current == nullptr || current->next == nullptr) {
      return nullptr;
    }
    if (current->val == 0) {
      return current;
    }
    accumulator->val += current->val;
    return mergeSequence(accumulator, current->next);
  }

  ListNode* mergeNodes(ListNode* head) {
    // The beginning and the end are guaranteed to have Node->val = 0
    ListNode* iter = head;
    while (iter != nullptr) {
      iter->next = mergeSequence(iter, iter->next);
      iter = iter->next;
    }
    return head;
  }
};
