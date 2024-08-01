package lc237

import "gitlab.com/euchangxian/leetcode/Go/internal/linkedlist"

func wrappedDeleteNode(head *linkedlist.ListNode, node *linkedlist.ListNode) *linkedlist.ListNode {
	deleteNode(node)
	return head
}

func deleteNode(node *linkedlist.ListNode) {
	delete(node)
}

func delete(node *linkedlist.ListNode) *linkedlist.ListNode {
	if node == nil || node.Next == nil {
		return nil
	}
	node.Val = node.Next.Val
	node.Next = delete(node.Next)
	return node
}
