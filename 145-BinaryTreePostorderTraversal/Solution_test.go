package lc145

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"gitlab.com/euchangxian/leetcode/internal/bst"
)

func TestPostorderTraversal(t *testing.T) {
	multipleNodes := &bst.TreeNode{
		Right: &bst.TreeNode{
			Left: &bst.TreeNode{
				Val: 3,
			},
			Val: 2,
		},
		Val: 1,
	}

	var emptyTree *bst.TreeNode

	singleNode := &bst.TreeNode{
		Val: 1,
	}

	testCases := []struct {
		name     string
		input    *bst.TreeNode
		expected []int
	}{
		{
			name:     "Multiple Nodes",
			input:    multipleNodes,
			expected: []int{3, 2, 1},
		},
		{
			name:     "No Nodes",
			input:    emptyTree,
			expected: nil,
		},
		{
			name:     "Single Node",
			input:    singleNode,
			expected: []int{1},
		},
	}

	for _, tc := range testCases {
		t.Run(tc.name, func(t *testing.T) {
			actual := PostorderTraversal(tc.input)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
