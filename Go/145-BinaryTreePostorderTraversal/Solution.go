package lc145

import (
	"gitlab.com/euchangxian/leetcode/Go/internal/bst"
)

func PostorderTraversal(root *bst.TreeNode) []int {
	var result []int
	search(&result, root)
	return result
}

func search(result *[]int, node *bst.TreeNode) {
	if node == nil {
		return
	}

	search(result, node.Left)
	search(result, node.Right)
	*result = append(*result, node.Val)
}
