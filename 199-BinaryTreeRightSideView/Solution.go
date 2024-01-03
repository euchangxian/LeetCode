package lc199

type TreeNode struct {
	Left  *TreeNode
	Right *TreeNode
	Val   int
}

// RightSideView returns the values of the nodes as seen from the right side of the tree, ordered
// from top to bottom.
// Approach: Level by level, pick the right-most node => LevelOrderSearch.
func RightSideView(root *TreeNode) []int {
	var result []int
	levelOrderSearch(&result, root)
	return result
}

func levelOrderSearch(result *[]int, root *TreeNode) {
	if root == nil {
		return
	}

	var frontier Queue // Slice-backed Queue

	frontier.Enqueue(root) // Initialize the Queue; Add the root node
	for !frontier.IsEmpty() {
		var nextFrontier Queue
		hasRightMost := false // Flag to add only the right-most node of each frontier to the results

		for !frontier.IsEmpty() {
			currentNode := frontier.Dequeue()
			if !hasRightMost {
				*result = append(*result, currentNode.Val)
				hasRightMost = true
			}

			// Adds TreeNode.Right, then TreeNode.Left. In this way, the first node popped from
			// each frontier will always be the right-most node, and will be in the result. *result = append(*result, currentNode.Val)
			if currentNode.Right != nil {
				nextFrontier = append(nextFrontier, currentNode.Right)
			}
			if currentNode.Left != nil {
				nextFrontier = append(nextFrontier, currentNode.Left)
			}
		}
		frontier = nextFrontier
	}
}

type Queue []*TreeNode

func (q *Queue) IsEmpty() bool {
	return len(*q) == 0 // Assumes len() will never return negative.
}

func (q *Queue) Enqueue(node *TreeNode) {
	*q = append(*q, node)
}

func (q *Queue) Dequeue() *TreeNode {
	popped := (*q)[0] // Retrieves the first element in the Queue
	*q = (*q)[1:]     // Slices the Queue, removing the first element
	return popped
}
