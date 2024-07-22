package lc3075

import "slices"

func maximumHappinessSum(happiness []int, k int) int64 {
	slices.SortFunc(happiness, func(i int, j int) int {
		// sort in descending/non-increasing order
		return j - i
	})

	var sum int64 = 0
	for i, x := range happiness[:k] {
		if x-i < 0 {
			break
		}
		sum += int64(x - i)
	}
	return sum
}
