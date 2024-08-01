package lc120

import "slices"

func minimumTotal(triangle [][]int) int {
	// Initialise to size of last row. Formulaically, every row is +1 the length of the
	// previous row, so it can simply be len(triangle).
	n := len(triangle[len(triangle)-1])
	// After the i-th iteration, dp[j] represents the minimum path sum to reach the
	// j-th number of the i-th row.
	dp := make([]int, n)
	dp[0] = triangle[0][0]

	for i := 1; i < len(triangle); i++ {
		temp := make([]int, n) // temporary dp array to store results of current iteration
		temp[0] = dp[0] + triangle[i][0]
		for j := 1; j < len(triangle[i]); j++ {
			// min(j, len(triangle[i-1]) - 1) handles the case when the current element does not have
			// an element directly above it i.e. a corner element.
			temp[j] = min(dp[j-1], dp[min(j, len(triangle[i-1])-1)]) + triangle[i][j]
		}
		dp = temp
	}
	return slices.Min(dp)
}
