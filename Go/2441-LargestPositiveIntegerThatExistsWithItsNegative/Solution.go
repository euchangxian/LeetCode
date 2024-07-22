package lc2441

func findMaxK(nums []int) int {
	maxK := -1

	seen := make(map[int]bool)

	for _, num := range nums {
		// Negate num to retrieve -k given k, or k given -k
		if !seen[-num] {
			seen[num] = true
			continue
		}

		absNum := max(num, -num)
		if absNum > maxK {
			maxK = absNum
		}
	}
	return maxK
}
