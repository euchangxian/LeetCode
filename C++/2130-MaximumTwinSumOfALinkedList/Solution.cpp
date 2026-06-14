#include <algorithm>

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
  int pairSum(ListNode* head) {
    // Even-length N linked list.
    // ith node is the twin of the (n-1-i)th node, if 0<=i<=(n/2)-1.
    // Twin sum if defined as the sum of a node and its twin.
    // Return the maximum twin sum of the linked list.
    constexpr auto reverse = [](this auto&& reverse,
                                ListNode* head) -> ListNode* {
      if (head == nullptr || head->next == nullptr) {
        return head;
      }
      auto* newHead = reverse(head->next);

      // head -> next -> next
      // 1 -> 2 -> nullptr
      head->next->next = head;
      head->next = nullptr;
      return newHead;
    };

    auto* slow = head;
    auto* fast = head;
    for (; fast != nullptr && fast->next != nullptr;
         slow = slow->next, fast = fast->next->next) {
    }

    auto* revHead = reverse(slow);
    auto result = 0;
    for (; revHead != nullptr; head = head->next, revHead = revHead->next) {
      result = std::max(result, head->val + revHead->val);
    }
    return result;
  }
};
