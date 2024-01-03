package lc145

type TreeNode struct {
	Left  *TreeNode
	Right *TreeNode
	Val   int
}

func PostorderTraversal(root *TreeNode) []int {
	var result []int
	search(&result, root)
	return result
}

func search(result *[]int, node *TreeNode) {
	if node == nil {
		return
	}

	search(result, node.Left)
	search(result, node.Right)
	*result = append(*result, node.Val)
}
