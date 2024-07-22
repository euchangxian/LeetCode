package lc739

func dailyTemperatures(temperatures []int) []int {
	result := make([]int, len(temperatures))

	// Stack stores indices i such that for all i, j in {0, ..., n-1}, i != j, i < j,
	// temperatures[i] >= temperatures[j]
	// i.e. temperatures that are monotonically non-increasing.
	// Initialized with a capacity the size of temperatures array to avoid unnecessary resizing.
	indices := make([]int, 0, len(temperatures))

	// Iterate through the daily temperatures
	for i, dailyTemp := range temperatures {
		// If stack is non-empty, let the temperature represented by the index on the top of the stack be x.
		// Then, there are two possible cases:
		// Case 1: Current dailyTemp is less than or equal to x.
		//         Then, simply add dailyTemp to the stack and continue
		// Case 2: Current dailyTemp is greater than (warmer!) than x.
		//         Then, pop x and update the resultant array, since we found a warmer day.
		//         Repeat until either the stack is empty, or dailyTemp is less than or equal to x.
		//         Add dailyTemp to the stack.
		for len(indices) != 0 {
			topIndex := indices[len(indices)-1] // peek at the top of the stack
			topTemperature := temperatures[topIndex]

			// Case 1
			if dailyTemp <= topTemperature {
				break // Move on to the next day
			}

			// Case 2
			// pop topTemperature and update number of days till warmer day
			indices = indices[:len(indices)-1]
			result[topIndex] = i - topIndex
		}
		// For both cases, add the index of the current temperature to the stack.
		indices = append(indices, i)
	}

	// If the stack is still non-empty after iterating through all elements, then we know that
	// the temperatures in the stack cannot have warmer days, and should be set to 0. (monotonically decreasing)
	// Though, the result array is already intiialized to zero, thus this loop is not required.
	// for _, index := range indices {
	//   result[index] = 0
	// }
	return result
}
