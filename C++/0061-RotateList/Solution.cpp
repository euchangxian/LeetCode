#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

using namespace std;
class Solution {
 private:
  int countNodes(ListNode* head, int length) {
    if (!head) {
      return length;
    }
    return countNodes(head->next, length + 1);
  }

 public:
  ListNode* rotateRight(ListNode* head, int k) {
    // k can be more than the length of the list, in that case, it will
    // circle back.
    int size = countNodes(head, 0);
    if (!head || !head->next || k == 0 || k % size == 0) {
      return head;
    }

    k = k % size;

    ListNode* newTail = head;
    // size - k represents the kth node from the back. Iterate 1 less to get
    // the newTail node
    for (int i = 0; i < size - k - 1; ++i) {
      newTail = newTail->next;
    }

    // The newHead of the list will be the next node.
    ListNode* newHead = newTail->next;

    ListNode* remaining = newHead;  // nodes after the newHead
    while (remaining->next) {
      remaining = remaining->next;
    }

    remaining->next = head;
    newTail->next = nullptr;

    return newHead;
  }
};
