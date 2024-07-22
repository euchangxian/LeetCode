package lc881

import "slices"

// Optimal Substructure:
// For any pair of persons that belong on a single boat in an optimal solution,
// $minBoats(people) = 1 + minBoats(people\{w_1, w_2})$
//
// Greedy Choice Propery:
// If there exists a pair {w_1, w_2} that fit onto a single boat in an optimal
// solution, then there must be a pair that includes the smallest file in **some**
// optimal solution.
//
// O(n + k) where k is the limit.
// Benchmarks show that the Comparison-based implementation runs faster/has a lower time per operation
// than the counting sort-based implementation. This is due to the relatively small size of the array
// used in the test as compared to the range of the integer.
//
// Similar to CS3230 Greedy Algorithms Tutorial
func numRescueBoats(people []int, limit int) int {
	countingSort(people, limit)

	numBoats := 0
	lightestIndex := 0
	heaviestIndex := len(people) - 1
	for lightestIndex <= heaviestIndex {
		lighest := people[lightestIndex]
		heaviest := people[heaviestIndex]

		if lighest+heaviest > limit {
			heaviestIndex--
		}
		if lighest+heaviest <= limit {
			lightestIndex++
			heaviestIndex--
		}
		numBoats += 1
	}

	return numBoats
}

// Sorts the given array in-place using Counting Sort.
// Not Stable.
// O(k + n) where k is the maximum possible value of the integers in the array.
func countingSort(arr []int, k int) {
	frequencies := make([]int, k+1)
	for _, num := range arr {
		frequencies[num]++
	}

	index := 0
	for num, freq := range frequencies {
		if freq == 0 {
			continue
		}
		for j := 0; j < freq; j++ {
			arr[index] = num
			index++
		}
	}
}

// Sorted using a Comparison-Based sorting algorithm.
// O(nlogn)
func numRescueBoatsComparisonBasedSorting(people []int, limit int) int {
	slices.Sort(people)

	numBoats := 0
	lightestIndex := 0
	heaviestIndex := len(people) - 1
	for lightestIndex <= heaviestIndex {
		lighest := people[lightestIndex]
		heaviest := people[heaviestIndex]

		if lighest+heaviest > limit {
			heaviestIndex--
		}
		if lighest+heaviest <= limit {
			lightestIndex++
			heaviestIndex--
		}
		numBoats += 1
	}

	return numBoats
}
