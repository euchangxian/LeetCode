package lc199

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"gitlab.com/euchangxian/leetcode/Go/internal/bst"
)

//		 1
//	 / \
//
// 2   3
//
//	 \   \
//		 5   4
var multipleLevels = &bst.TreeNode{
	Val: 1,
	Left: &bst.TreeNode{
		Val: 2,
		Right: &bst.TreeNode{
			Val: 5,
		},
	},
	Right: &bst.TreeNode{
		Val: 3,
		Right: &bst.TreeNode{
			Val: 4,
		},
	},
}

var emptyTree *bst.TreeNode

// 1
//
//	3
var oneLevel = &bst.TreeNode{
	Val: 1,
	Right: &bst.TreeNode{
		Val: 3,
	},
}

func TestRightSideView(t *testing.T) {
	testCases := map[string]struct {
		input    *bst.TreeNode
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
			t.Parallel()
			actual := RightSideView(tc.input)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
