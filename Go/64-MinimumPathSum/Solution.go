package lc64

func minPathSum(grid [][]int) int {
	n, m := len(grid), len(grid[0])

	// dp[j] represents the minimum path sum obtainable after the i-th iteration
	dp := make([]int, m)

	// Set up base case for first row
	dp[0] = grid[0][0]
	for i := 1; i < m; i++ {
		dp[i] = grid[0][i] + dp[i-1]
	}

	for i := 1; i < n; i++ {
		temp := make([]int, m) // avoid using results from current iteration
		temp[0] = grid[i][0] + dp[0]
		for j := 1; j < m; j++ {
			temp[j] = grid[i][j] + min(dp[j], temp[j-1])
		}
		dp = temp
	}

	return dp[m-1]
}
