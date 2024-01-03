package lc144

type TreeNode struct {
	Left  *TreeNode
	Right *TreeNode
	Val   int
}

func PreorderTraversal(root *TreeNode) []int {
	var result []int
	search(&result, root)
	return result
}

func search(result *[]int, node *TreeNode) {
	if node == nil {
		return
	}
	*result = append(*result, node.Val)
	search(result, node.Left)
	search(result, node.Right)
}
