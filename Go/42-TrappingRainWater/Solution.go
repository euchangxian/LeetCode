package lc42

type IntStack []int

// The calculation of the exact unit amount of water trapped can be
// visualized as a histogram, where due to the monotonically decreasing
// property of our stack, we can inductively add to the resultant amount of
// water trapped. To elaborate, suppose we have some arbitrary indices
// {0, 1, 2} representing elevations {3, 2, 1} in the Stack, and we
// encounter an elevation of 4 at index 3.
//
// We first pop the most minimum value in the stack, with (index,
// elevation) corresponding to (2, 1). Then, looking to its left, we have
// (1, 2). The amount of water trapped by this set of elevations is simply
// the difference of min(leftBound, rightBound) = min(2, 4) = 2 and the
// popped value 1. Thus we get 1 unit of water trapped.
//
// The next iteration, we pop (1, 2) and look at (0, 3). The height of
// water bounded will be
// `min(leftBound, rightBound) - popped = min(3, 4) = 3 - 2 = 1 unit`
// As such, we add 1 unit of water to the result. However, this does not
// account for the previously popped (2, 1), which has a lower elevation
// than the current popped (1, 2), and will therefore have the same height
// of trapped water. Thus we find the horizontal distance between the
// leftBound and rightBound, denoted by `i - len(indices) - 1`, and
// multiply it by the height of water added in the current iteration,
// giving us the correct result of 3 units of water trapped for the current
// iteration.
func trap(height []int) int {
	if len(height) < 3 {
		// Water cannot be trapped
		return 0
	}

	// Monotonically decreasing stack.
	// Look for an elevation that is equal to or higher than the top of the stack.
	indices := make(IntStack, 0, len(height))

	result := 0
	for i, currentElevation := range height {
		for !indices.isEmpty() && currentElevation > height[indices.peek()] {
			// Pop top-most of the stack
			topMostElevation := height[indices.pop()]

			// No left boundary i.e. initial size of stack < 3
			if indices.isEmpty() {
				break
			}

			// Check left boundary of popped left elevation
			leftElevation := height[indices.peek()]

			// Calculate the height of the water trapped **between** the currentElevation and the leftElevation
			boundedHeight := min(leftElevation, currentElevation) - topMostElevation

			// Trickiest part.
			result += boundedHeight * (i - indices.peek() - 1)
		}

		indices.push(i)
	}

	return result
}

func (s *IntStack) push(val int) {
	*s = append(*s, val)
}

// Assumes an isEmpty check is done already.
func (s *IntStack) pop() int {
	popped := (*s)[len(*s)-1]
	*s = (*s)[:len(*s)-1]
	return popped
}

func (s *IntStack) peek() int {
	top := (*s)[len(*s)-1]
	return top
}

func (s *IntStack) isEmpty() bool {
	return len(*s) == 0
}
