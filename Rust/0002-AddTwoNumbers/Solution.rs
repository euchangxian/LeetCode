pub struct Solution {}

use crate::commons::linked_list::ListNode;

impl Solution {
    pub fn add_two_numbers(
        l1: Option<Box<ListNode>>,
        l2: Option<Box<ListNode>>,
    ) -> Option<Box<ListNode>> {
        match (l1, l2) {
            (None, None) => None, // If both l1 and l2 are None (null)
            (Some(n), None) | (None, Some(n)) => Some(n), // No need to add
            (Some(n1), Some(n2)) => {
                let sum = n1.val + n2.val;
                if sum > 9 {
                    let carry = Some(Box::new(ListNode::new(1)));
                    return Some(Box::new(ListNode {
                        val: sum - 10,
                        next: Solution::add_two_numbers(
                            Solution::add_two_numbers(carry, n1.next),
                            n2.next,
                        ),
                    }));
                }
                Some(Box::new(ListNode {
                    val: sum,
                    next: Solution::add_two_numbers(n1.next, n2.next),
                }))
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_add_two_numbers() {
        assert_eq!(
            ListNode::from_vector(vec![7, 0, 8]),
            Solution::add_two_numbers(
                ListNode::from_vector(vec![2, 4, 3]),
                ListNode::from_vector(vec![5, 6, 4])
            )
        );
        assert_eq!(
            ListNode::from_vector(vec![0]),
            Solution::add_two_numbers(
                ListNode::from_vector(vec![0]),
                ListNode::from_vector(vec![0])
            )
        );
        assert_eq!(
            ListNode::from_vector(vec![8, 9, 9, 9, 0, 0, 0, 1]),
            Solution::add_two_numbers(
                ListNode::from_vector(vec![9, 9, 9, 9, 9, 9, 9]),
                ListNode::from_vector(vec![9, 9, 9, 9])
            )
        );
    }
}
