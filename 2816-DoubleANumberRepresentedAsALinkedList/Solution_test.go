package lc2816

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"gitlab.com/euchangxian/leetcode/internal/linkedlist"
)

var head = &linkedlist.ListNode{
	Val: 9,
	Next: &linkedlist.ListNode{
		Val: 9,
		Next: &linkedlist.ListNode{
			Val:  9,
			Next: nil,
		},
	},
}

func TestDoubleIt(t *testing.T) {
	testCases := map[string]struct {
		head     *linkedlist.ListNode
		expected *linkedlist.ListNode
	}{
		"Double 999 to form 1998. Should insert node with value 1 in front of head.": {
			head: head,
			expected: &linkedlist.ListNode{
				Val: 1,
				Next: &linkedlist.ListNode{
					Val: 9,
					Next: &linkedlist.ListNode{
						Val: 9,
						Next: &linkedlist.ListNode{
							Val:  8,
							Next: nil,
						},
					},
				},
			},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := doubleIt(tc.head)
			for tc.expected != nil {
				assert.Equal(t, tc.expected.Val, actual.Val)
				tc.expected = tc.expected.Next
				actual = actual.Next
			}
		})
	}
}
