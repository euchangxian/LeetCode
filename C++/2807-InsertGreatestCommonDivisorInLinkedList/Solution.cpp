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
  ListNode* insertGreatestCommonDivisors(ListNode* head) {
    if (!head || !head->next) {
      // Base case, single node only
      return head;
    }

    ListNode* next = head->next;
    head->next = new ListNode(gcd(head->val, next->val), next);
    head->next->next = insertGreatestCommonDivisors(next);
    return head;
  }

 private:
  int gcd(int a, int b) {
    if (b == 0) {
      return a;
    }
    return gcd(b, a % b);
  }
};
