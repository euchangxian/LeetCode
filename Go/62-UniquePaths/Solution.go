package lc62

func uniquePaths(m int, n int) int {
	// After the i-th iteration, dp[j] represents the number of ways to reach cell (i, j)
	dp := make([]int, n)
	// Base case. Only 1 way to reach anything on the first row.
	for j := range dp {
		dp[j] = 1
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			dp[j] += dp[j-1]
		}
	}
	return dp[n-1]
}
