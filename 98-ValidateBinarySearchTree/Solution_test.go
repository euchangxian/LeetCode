package lc98

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"gitlab.com/euchangxian/leetcode/internal/bst"
)

// --2
// 1---3
var validBST = &bst.TreeNode{
	Val: 2,
	Left: &bst.TreeNode{
		Val: 1,
	},
	Right: &bst.TreeNode{
		Val: 3,
	},
}

var validBSTMinMaxInt = &bst.TreeNode{
	Val: -2147483648,
	Right: &bst.TreeNode{
		Val: 2147483647,
	},
}

// --5
// 1---4
// ---3---6
var invalidBSTRightChild = &bst.TreeNode{
	Val: 5,
	Left: &bst.TreeNode{
		Val: 1,
	},
	Right: &bst.TreeNode{
		Val: 4,
		Left: &bst.TreeNode{
			Val: 3,
		},
		Right: &bst.TreeNode{
			Val: 6,
		},
	},
}

// ----- 5
// --- 4 -- 6
// ------- 3 7
var invalidBSTRightLeaf = &bst.TreeNode{
	Val: 5,
	Left: &bst.TreeNode{
		Val: 4,
	},
	Right: &bst.TreeNode{
		Val: 6,
		Left: &bst.TreeNode{
			Val: 3,
		},
		Right: &bst.TreeNode{
			Val: 7,
		},
	},
}

func TestIsValidBST(t *testing.T) {
	testCases := map[string]struct {
		input    *bst.TreeNode
		expected bool
	}{
		"Valid BST - Empty Tree": {
			input:    nil,
			expected: true,
		},
		"Valid BST - Trivial Case": {
			input:    validBST,
			expected: true,
		},
		"Valid BST - Min / Max integer value nodes": {
			input:    validBSTMinMaxInt,
			expected: true,
		},
		"Invalid BST - Right child is less than root": {
			input:    invalidBSTRightChild,
			expected: false,
		},
		"Invalid BST - Right leaf is less than root": {
			input:    invalidBSTRightLeaf,
			expected: false,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := IsValidBST(tc.input)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
