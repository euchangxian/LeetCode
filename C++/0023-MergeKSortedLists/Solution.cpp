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
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

using namespace std;
class Solution {
private:
  ListNode *mergeLists(ListNode *l1, ListNode *l2) {
    if (!l1) {
      return l2;
    }
    if (!l2) {
      return l1;
    }

    if (l1->val <= l2->val) {
      l1->next = mergeLists(l1->next, l2);
      return l1;
    }

    l2->next = mergeLists(l1, l2->next);
    return l2;
  }

public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    if (lists.empty()) {
      return nullptr;
    }

    int interval = 1;
    while (interval < lists.size()) {
      for (int i = 0; i + interval < lists.size(); i += (interval * 2)) {
        lists[i] = mergeLists(lists[i], lists[i + interval]);
      }
      interval *= 2;
    }

    return lists[0];
  }
};

