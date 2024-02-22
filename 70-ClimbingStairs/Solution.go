package lc70

func climbStairs(n int) int {
	if n < 2 {
		return 1
	}
	// Array of size n
	dp := make([]int, n)

	// Base case n == 1 => only 1 way
	dp[0] = 1

	// Add another base case for simplification of loop
	dp[1] = 2

	for i := 2; i < n; i++ {
		dp[i] = dp[i-1] + dp[i-2]
	}

	return dp[n-1]
}
