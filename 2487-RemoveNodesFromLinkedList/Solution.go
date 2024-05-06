package lc2487

import "gitlab.com/euchangxian/leetcode/internal/linkedlist"

func removeNodes(head *linkedlist.ListNode) *linkedlist.ListNode {
	if head == nil {
		return nil
	}
	if head.Next == nil {
		return head
	}

	head.Next = removeNodes(head.Next)
	if head.Next.Val > head.Val {
		return head.Next
	}
	return head
}
