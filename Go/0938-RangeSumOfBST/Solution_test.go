package lc938

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"gitlab.com/euchangxian/leetcode/Go/internal/bst"
)

//	    10
//	5       15
//
// 3    7         18
var input1 = &bst.TreeNode{
	Val: 10,
	Left: &bst.TreeNode{
		Val: 5,
		Left: &bst.TreeNode{
			Val: 3,
		},
		Right: &bst.TreeNode{
			Val: 7,
		},
	},
	Right: &bst.TreeNode{
		Val: 15,
		Right: &bst.TreeNode{
			Val: 18,
		},
	},
}

//	        10
//	   5          15
//	3     7    13   18
//
// 1         6
var input2 = &bst.TreeNode{
	Val: 10,
	Left: &bst.TreeNode{
		Val: 5,
		Left: &bst.TreeNode{
			Val: 3,
			Left: &bst.TreeNode{
				Val: 1,
			},
		},
		Right: &bst.TreeNode{
			Val: 7,
			Left: &bst.TreeNode{
				Val: 6,
			},
		},
	},
	Right: &bst.TreeNode{
		Val: 15,
		Left: &bst.TreeNode{
			Val: 13,
		},
		Right: &bst.TreeNode{
			Val: 18,
		},
	},
}

func TestRangeSumBST(t *testing.T) {
	testCases := map[string]struct {
		inputTree *bst.TreeNode
		low       int
		high      int
		expected  int
	}{
		"Small tree": {
			inputTree: input1,
			low:       7,
			high:      15,
			expected:  32,
		},
		"Big tree": {
			inputTree: input2,
			low:       6,
			high:      10,
			expected:  23,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := RangeSumBST(tc.inputTree, tc.low, tc.high)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
