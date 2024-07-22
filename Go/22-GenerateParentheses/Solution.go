package lc22

// generateParenthesis returns the set of well-formed Parentheses that can be made by n pairs
//
// This follows the sequence of Catalan Numbers, and has the following recursive formulation:
// "" in C (i.e. empty string is in the set)
// if a and b in C, then (a)b is in C.
//
// Therefore, C_n = {(C_0)C_n-1, (C_1)C_n-2, ..., (C_n-1)C_0}
// |C_n| = (1/n+1)*(2nCn)  (1 over n+1  times  2n Choose n)
// => number of ways to choose n pairs among 2n pairs, normalized by 1/(n+1).
func generateParenthesis(n int) []string {
	dp := make([][]string, n+1) // Include n=0 base case.

	// Base case: empty string
	dp[0] = []string{""}

	for i := 1; i < n+1; i++ {
		for j := 0; j < i; j++ {
			// Iterate and form pairs over C_j and C_i-j-1
			for _, alpha := range dp[j] {
				for _, beta := range dp[i-j-1] {
					dp[i] = append(dp[i], "("+alpha+")"+beta)
				}
			}
		}
	}
	return dp[n]
}
