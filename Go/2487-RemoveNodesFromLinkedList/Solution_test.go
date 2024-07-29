package lc2487

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"gitlab.com/euchangxian/leetcode/Go/internal/linkedlist"
)

var head = &linkedlist.ListNode{
	Val: 5,
	Next: &linkedlist.ListNode{
		Val: 2,
		Next: &linkedlist.ListNode{
			Val: 13,
			Next: &linkedlist.ListNode{
				Val: 3,
				Next: &linkedlist.ListNode{
					Val:  8,
					Next: nil,
				},
			},
		},
	},
}

func TestDeleteNode(t *testing.T) {
	testCases := map[string]struct {
		head     *linkedlist.ListNode
		node     *linkedlist.ListNode
		expected *linkedlist.ListNode
	}{
		"Nodes with greater value may not be adjacent": {
			head: head,
			node: head.Next,
			expected: &linkedlist.ListNode{
				Val: 13,
				Next: &linkedlist.ListNode{
					Val:  8,
					Next: nil,
				},
			},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := removeNodes(tc.head)
			for tc.expected != nil {
				assert.Equal(t, tc.expected.Val, actual.Val)
				tc.expected = tc.expected.Next
				actual = actual.Next
			}
		})
	}
}
