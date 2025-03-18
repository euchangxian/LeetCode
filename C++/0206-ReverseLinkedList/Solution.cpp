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
  ListNode* reverseList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    // Traverse all the way to the tail and store it as the new head to be
    // returned. Wishfully reverse the list
    ListNode* newHead = reverseList(head->next);

    // head -> next -> next
    // 1 -> 2 -> nullptr
    head->next->next = head;  // 1 -> 2 -> 1 (circle)
    head->next = nullptr;     // 2 -> 1 -> nullptr

    return newHead;
  }
};
