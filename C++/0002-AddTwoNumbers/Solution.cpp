#include <algorithm>
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
  ListNode* addWithCarry(ListNode* l1, ListNode* l2, int carry) {
    if (!l1 && !l2 && carry == 0) {
      return nullptr;  // end of number
    }

    int l1Val = 0;
    int l2Val = 0;
    ListNode* l1Next = nullptr;
    ListNode* l2Next = nullptr;

    if (l1) {
      l1Val = l1->val;
      l1Next = l1->next;
    }

    if (l2) {
      l2Val = l2->val;
      l2Next = l2->next;
    }

    int sum = l1Val + l2Val + carry;
    return new ListNode(sum % 10, addWithCarry(l1Next, l2Next, sum / 10));
  }

 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    return addWithCarry(l1, l2, 0);
  }
};
