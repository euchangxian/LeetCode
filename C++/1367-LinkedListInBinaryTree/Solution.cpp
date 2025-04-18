#ifdef LOCAL
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};
#endif  // LOCAL

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
  bool isSubPath(ListNode* head, TreeNode* root) {
    if (!head) {
      return true;
    }
    if (!root) {
      return false;
    }

    if (isSame(head, root)) {
      return true;
    }

    return isSubPath(head, root->left) || isSubPath(head, root->right);
  }

 private:
  bool isSame(ListNode* head, TreeNode* root) {
    if (!head) {
      return true;
    }
    if (!root) {
      return false;
    }

    if (head->val != root->val) {
      return false;
    }

    return isSame(head->next, root->left) || isSame(head->next, root->right);
  }
};
