use std::cell::RefCell;
use std::rc::Rc;

#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

pub fn from_vec(vec: Vec<Option<i32>>) -> Option<Rc<RefCell<TreeNode>>> {
    // Create the root node from the first element
    let root = match vec.get(0) {
        Some(Some(value)) => Some(Rc::new(RefCell::new(TreeNode::new(*value)))),
        _ => return None, // Return None if the input vector is empty or the first element is None
    };

    let mut queue = std::collections::VecDeque::new();
    if let Some(ref root_node) = root {
        queue.push_back(Rc::clone(root_node));
    }

    // Process the rest of the elements in pairs (left, right)
    for children in vec[1..].chunks(2) {
        if let Some(parent) = queue.pop_front() {
            // Handle the left child
            if let Some(left_value) = children.get(0).and_then(|&v| v) {
                let left_child = Rc::new(RefCell::new(TreeNode::new(left_value)));
                parent.borrow_mut().left = Some(Rc::clone(&left_child));
                queue.push_back(left_child);
            }

            // Handle the right child
            if let Some(right_value) = children.get(1).and_then(|&v| v) {
                let right_child = Rc::new(RefCell::new(TreeNode::new(right_value)));
                parent.borrow_mut().right = Some(Rc::clone(&right_child));
                queue.push_back(right_child);
            }
        }
    }

    root
}
