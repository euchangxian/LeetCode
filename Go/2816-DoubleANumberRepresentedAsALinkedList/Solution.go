package lc2816

import "gitlab.com/euchangxian/leetcode/Go/internal/linkedlist"

func doubleIt(head *linkedlist.ListNode) *linkedlist.ListNode {
	carry := double(head)

	if carry > 0 {
		return &linkedlist.ListNode{
			Val:  carry,
			Next: head,
		}
	}
	return head
}

func double(node *linkedlist.ListNode) int {
	if node == nil {
		return 0
	}
	doubledVal := node.Val*2 + double(node.Next)

	node.Val = doubledVal % 10

	return doubledVal / 10
}
