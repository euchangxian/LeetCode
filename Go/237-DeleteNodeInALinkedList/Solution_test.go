package lc237

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"gitlab.com/euchangxian/leetcode/internal/linkedlist"
)

var head = &linkedlist.ListNode{
	Val: 4,
	Next: &linkedlist.ListNode{
		Val: 5,
		Next: &linkedlist.ListNode{
			Val: 1,
			Next: &linkedlist.ListNode{
				Val:  9,
				Next: nil,
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
		"Delete second node from head": {
			head: head,
			node: head.Next,
			expected: &linkedlist.ListNode{
				Val: 4,
				Next: &linkedlist.ListNode{
					Val: 1,
					Next: &linkedlist.ListNode{
						Val:  9,
						Next: nil,
					},
				},
			},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := wrappedDeleteNode(tc.head, tc.node)
			for tc.expected != nil {
				assert.Equal(t, tc.expected.Val, actual.Val)
				tc.expected = tc.expected.Next
				actual = actual.Next
			}
		})
	}
}
