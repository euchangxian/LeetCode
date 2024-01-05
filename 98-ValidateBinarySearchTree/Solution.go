package lc98

import (
	"math"

	"gitlab.com/euchangxian/leetcode/internal/bst"
)

func IsValidBST(root *bst.TreeNode) bool {
	if root == nil {
		return true
	}

	return isValidChild(root.Left, math.MinInt64, root.Val) &&
		isValidChild(root.Right, root.Val, math.MaxInt64)
}

func isValidChild(node *bst.TreeNode, low int, high int) bool {
	if node == nil {
		return true
	}
	return isInRange(node.Val, low, high) &&
		isValidChild(node.Left, low, node.Val) &&
		isValidChild(node.Right, node.Val, high)
}

// isInRange evaluates whether a given value is in the range (low, high), exclusive.
func isInRange(val int, low int, high int) bool {
	return val > low && val < high
}
