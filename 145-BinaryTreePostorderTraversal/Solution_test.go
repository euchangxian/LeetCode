package lc145

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestPostorderTraversal(t *testing.T) {
	multipleNodes := &TreeNode{
		Right: &TreeNode{
			Left: &TreeNode{
				Val: 3,
			},
			Val: 2,
		},
		Val: 1,
	}

	var emptyTree *TreeNode

	singleNode := &TreeNode{
		Val: 1,
	}

	testCases := []struct {
		name     string
		input    *TreeNode
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
