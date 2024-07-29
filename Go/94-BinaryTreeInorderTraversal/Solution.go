package lc94

import (
	"gitlab.com/euchangxian/leetcode/Go/internal/bst"
)

type Result []int

func InorderTraversal(root *bst.TreeNode) []int {
	var result Result
	result.depthFirstSearch(root)
	return result
}

func (result *Result) depthFirstSearch(node *bst.TreeNode) {
	if node == nil {
		return
	}

	result.depthFirstSearch(node.Left)
	*result = append(*result, node.Val)
	result.depthFirstSearch(node.Right)
}
