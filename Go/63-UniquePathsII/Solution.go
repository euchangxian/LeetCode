package lc63

func uniquePathsWithObstacles(obstacleGrid [][]int) int {
	m := len(obstacleGrid)
	n := len(obstacleGrid[0])
	// After the i-th iteration, dp[j] represents the number of ways to reach cell (i, j)
	dp := make([]int, n)

	// Base case. Only 1 way to reach anything on the first row.
	for j := range dp {
		if obstacleGrid[0][j] == 1 {
			break
		}
		dp[j] = 1
	}

	for i := 1; i < m; i++ {
		for j := 0; j < n; j++ {
			if obstacleGrid[i][j] == 1 {
				dp[j] = 0
				continue
			}

			// Handle first column
			if j <= 0 {
				continue
			}
			dp[j] += dp[j-1]
		}
	}
	return dp[n-1]
}
