package lc1143

// Let n and m be the length of text1 and text2 respectively
// Recursive Recurrence: if a_n = b_m then LCS(n - 1, m - 1) + 1
// else: max(LCS(n - 1, m), LCS(n, m - 1))
// Base Case: if n == 0 || m == 0 then return 0
// O(nm) space-time complexity
func longestCommonSubsequence(text1 string, text2 string) int {
	n := len(text1)
	m := len(text2)
	// No need to explicitly set up base case: Go initializes elements to their zero-value
	dp := make([][]int, n+1) // (n + 1) x (m + 1) dp array
	for i := range dp {
		dp[i] = make([]int, m+1)
	}

	for i := 1; i < n+1; i++ {
		for j := 1; j < m+1; j++ {
			// i and j are 1-indexed / offset by 1 - base case is a row/column of 0s
			if text1[i-1] != text2[j-1] {
				dp[i][j] = max(dp[i-1][j], dp[i][j-1])
			} else {
				dp[i][j] = dp[i-1][j-1] + 1
			}
		}
	}

	return dp[n][m]
}

// O(nm) time complexity, but O(min(n, m)) space complexity i.e. 1-d DP
// Assumes m <= n => O(m) space complexity
// At the start of the i-th iteration, dp[j] = dp[i - 1][j] (prev row, j-th column)
// At the end of the i-th iteration, dp[j] = dp[i][j] (corresponds to LCS(n, m))
func lcs(text1 string, text2 string) int {
	n := len(text1)
	m := len(text2)
	// Simple check to ensure m <= n
	if n > m {
		return lcs(text2, text1)
	}

	// Think of it as iterating on the same row n times.
	dp := make([]int, m+1) // O(min(n, m)) = O(m)

	// Keep track of the previous diagonal and row, represented by dp[i-1][j-1] and dp[i-1][j] previously
	for i := 1; i < n+1; i++ {
		prevDiagonal := 0 // Base case when length of text1 = 0
		for j := 1; j < m+1; j++ {
			temp := dp[j] // Hold the current value of dp[j] before any update. Represents dp[i][j] in the (i+1)th iteration.
			if text1[i-1] != text2[j-1] {
				dp[j] = max(dp[j], dp[j-1])
			} else {
				dp[j] = prevDiagonal + 1
			}
			prevDiagonal = temp
		}
	}

	return dp[m]
}
