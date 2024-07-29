package lc938

import (
	"gitlab.com/euchangxian/leetcode/Go/internal/bst"
)

func RangeSumBST(root *bst.TreeNode, low int, high int) int {
	var sum int
	search(&sum, root, low, high)
	return sum
}

func search(sum *int, node *bst.TreeNode, low int, high int) {
	if node == nil {
		return
	}

	if inRange(node.Val, low, high) {
		*sum += node.Val
	}
	search(sum, node.Left, low, high)
	search(sum, node.Right, low, high)
}

// inRange evaluates whether a given val is in the range [low, high], inclusive.
func inRange(val int, low int, high int) bool {
	return val >= low && val <= high
}
