package lc118

func generate(numRows int) [][]int {
	dp := make([][]int, numRows)

	// Base case
	dp[0] = []int{1}

	for i := 1; i < numRows; i++ {
		row := make([]int, i+1) // i + 1 elements in the ith row, i is 0-indexed

		// Start and End of the row is 1
		row[0] = 1
		row[i] = 1

		// Calculate middle elements
		for j := 1; j < i; j++ {
			row[j] = dp[i-1][j-1] + dp[i-1][j]
		}

		dp[i] = row
	}
	return dp
}
