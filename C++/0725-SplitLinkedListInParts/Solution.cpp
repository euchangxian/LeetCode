#include <vector>

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
  std::vector<ListNode*> splitListToParts(ListNode* head, int k) {
    int size = listSize(head, 0);

    int partSize = size / k;

    // First size % k segments have an extra node
    int extras = size % k;

    std::vector<ListNode*> result(k, nullptr);

    ListNode* prev = nullptr;
    for (int i = 0; head && i < k; ++i) {
      result[i] = head;
      for (int j = 0; j < partSize; ++j) {
        prev = head;
        head = head->next;
      }

      if (i < extras) {
        prev = head;
        head = head->next;
      }

      prev->next = nullptr;  // Disconnect this segment
    }
    return result;
  }

 private:
  int listSize(ListNode* head, int len) {
    if (!head) {
      return len;
    }

    return listSize(head->next, 1 + len);
  }
};
