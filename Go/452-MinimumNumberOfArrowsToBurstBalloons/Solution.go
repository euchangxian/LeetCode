package lc452

import "slices"

func findMinArrowShots(points [][]int) int {
	// Sort the points array by the right element (ending x-coordinates) of each pair in ascending order.
	slices.SortFunc(points, func(a []int, b []int) int {
		return a[1] - b[1]
	})

	shots := 1
	currentEnd := points[0][1]
	// Optimal Substructure: if interval [start, end] is picked in the optimal solution,
	// we can recurse on the subproblem where the interval, and any other overlapping intervals
	// are removed.
	// Greedy Choice: There is always an optimal solution where the balloon with the earliest ending
	// x-coordinates is picked (the arrow is shot in that interval)
	for i := 1; i < len(points); i++ {
		currentPair := points[i]

		if currentPair[0] > currentEnd {
			// No overlap in interval.
			shots++
			currentEnd = currentPair[1]
		}
	}
	return shots
}
