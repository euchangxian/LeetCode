package lc199

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

//		 1
//	 / \
//
// 2   3
//
//	 \   \
//		 5   4
var multipleLevels = &TreeNode{
	Val: 1,
	Left: &TreeNode{
		Val: 2,
		Right: &TreeNode{
			Val: 5,
		},
	},
	Right: &TreeNode{
		Val: 3,
		Right: &TreeNode{
			Val: 4,
		},
	},
}

var emptyTree *TreeNode

// 1
//
//	3
var oneLevel = &TreeNode{
	Val: 1,
	Right: &TreeNode{
		Val: 3,
	},
}

func TestRightSideView(t *testing.T) {
	testCases := map[string]struct {
		input    *TreeNode
		expected []int
	}{
		"Multiple levels": {
			input:    multipleLevels,
			expected: []int{1, 3, 4},
		},
		"Empty tree": {
			input:    emptyTree,
			expected: nil,
		},
		"One level": {
			input:    oneLevel,
			expected: []int{1, 3},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			actual := RightSideView(tc.input)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
