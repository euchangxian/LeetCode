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
 private:
  ListNode* removeFromBack(ListNode* curr, int const n, int& k) {
    if (!curr) {
      return nullptr;
    }

    curr->next = removeFromBack(curr->next, n, k);
    ++k;
    if (k == n) {
      // skip the current node. Also handles the case where the head needs to be
      // removed
      return curr->next;
    }
    return curr;
  }

 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    int k = 0;
    return removeFromBack(head, n, k);
  }
};
