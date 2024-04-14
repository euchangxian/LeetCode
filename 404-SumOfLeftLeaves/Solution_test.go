package lc404

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"gitlab.com/euchangxian/leetcode/internal/bst"
)

func TestSumOfLeftLeaves(t *testing.T) {
	multipleNodes := &bst.TreeNode{
		Val: 3,
		Left: &bst.TreeNode{
			Val: 9,
		},
		Right: &bst.TreeNode{
			Val: 20,
			Left: &bst.TreeNode{
				Val: 15,
			},
			Right: &bst.TreeNode{
				Val: 7,
			},
		},
	}

	var emptyTree *bst.TreeNode

	singleNode := &bst.TreeNode{
		Val: 1,
	}

	testCases := map[string]struct {
		input    *bst.TreeNode
		expected int
	}{
		"Two left leaves: 9 and 12": {
			input:    multipleNodes,
			expected: 24,
		},
		"Trivial case": {
			input:    emptyTree,
			expected: 0,
		},
		"A single node can not be a left child": {
			input:    singleNode,
			expected: 0,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := sumOfLeftLeaves(tc.input)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
