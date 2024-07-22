package lc144

import (
	"gitlab.com/euchangxian/leetcode/internal/bst"
)

func PreorderTraversal(root *bst.TreeNode) []int {
	var result []int
	search(&result, root)
	return result
}

func search(result *[]int, node *bst.TreeNode) {
	if node == nil {
		return
	}
	*result = append(*result, node.Val)
	search(result, node.Left)
	search(result, node.Right)
}
