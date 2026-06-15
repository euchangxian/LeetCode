#include <utility>

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
  ListNode* deleteMiddle(ListNode* head) {
    // Delete the middle node, return the head of the modified linked list.
    // floor(n/2)-th node from the start.
    //
    // slow-fast pointer.
    // Even: slow will be at the middle
    // Odd : slow will be one past the middle, if naively handled.
    //
    // E.g.,:
    //  _   _   _   _
    // s,f
    //      s   f
    //          s      f
    //
    //  _   _   _
    // s,f
    //      s   f
    //      s     f // slow not advanced if first advance of fast is null
    ListNode* prevSlow = nullptr;
    auto* slow = head;
    auto* fast = head;

    while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
      if ((fast = fast->next) == nullptr) {
        break;
      }
      fast = fast->next;
      prevSlow = std::exchange(slow, slow->next);
    }

    if (slow == head) {
      // n==1 or n==2
      return slow->next;
    }

    prevSlow->next = slow->next;
    return head;
  }
};
