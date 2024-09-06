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
  ListNode *removeNums(ListNode *curr, unordered_set<int> const &toRemove) {
    if (!curr) {
      return nullptr;
    }

    if (toRemove.count(curr->val)) {
      return removeNums(curr->next, toRemove);
    }

    curr->next = removeNums(curr->next, toRemove);
    return curr;
  }

public:
  ListNode *modifiedList(vector<int> &nums, ListNode *head) {
    // Remove lists matching nums
    unordered_set<int> toRemove(nums.begin(), nums.end());

    return removeNums(head, toRemove);
  }
};
