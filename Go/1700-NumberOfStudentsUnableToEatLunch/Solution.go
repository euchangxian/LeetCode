package lc1700

func countStudents(students []int, sandwiches []int) int {
	// preferences[0] represents students who prefer Circular andwiches,
	// preferences[1] represent students who prefer Square sandwiches
	preferences := []int{0, 0}

	for _, preference := range students {
		preferences[preference]++
	}

	for _, sandwich := range sandwiches {
		if preferences[sandwich] == 0 {
			return preferences[1-sandwich]
		}
		preferences[sandwich]--
	}
	return 0
}
