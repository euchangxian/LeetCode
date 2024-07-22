package lc404

import "gitlab.com/euchangxian/leetcode/internal/bst"

func sumOfLeftLeaves(root *bst.TreeNode) int {
	return helper(root, false)
}

func helper(node *bst.TreeNode, isLeft bool) int {
	if node == nil {
		return 0
	}
	toAdd := 0
	if isLeft && (node.Left == nil && node.Right == nil) {
		toAdd = node.Val
	}
	return toAdd + helper(node.Left, true) + helper(node.Right, false)
}
