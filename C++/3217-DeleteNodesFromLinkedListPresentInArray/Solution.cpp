#include <unordered_set>
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
  ListNode* modifiedList(std::vector<int>& nums, ListNode* head) {
    // Remove lists matching nums
    std::unordered_set<int> toRemove(nums.begin(), nums.end());

    return removeNums(head, toRemove);
  }

 private:
  ListNode* removeNums(ListNode* curr,
                       const std::unordered_set<int>& toRemove) {
    if (!curr) {
      return nullptr;
    }

    if (toRemove.count(curr->val)) {
      return removeNums(curr->next, toRemove);
    }

    curr->next = removeNums(curr->next, toRemove);
    return curr;
  }
};
