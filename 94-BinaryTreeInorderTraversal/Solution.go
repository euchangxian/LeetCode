package main

// TreeNode represents a binary tree node.
type TreeNode struct {
	Left  *TreeNode
	Right *TreeNode
	Val   int
}

type Result []int

func InorderTraversal(root *TreeNode) []int {
	var result Result
	result.depthFirstSearch(root)
	return result
}

func (result *Result) depthFirstSearch(node *TreeNode) {
	if node == nil {
		return
	}

	result.depthFirstSearch(node.Left)
	*result = append(*result, node.Val)
	result.depthFirstSearch(node.Right)
}
