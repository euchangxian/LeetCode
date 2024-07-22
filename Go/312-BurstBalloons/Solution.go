package lc312

// Recursive Formulation:
// $maxCoins(A[1..n]) = max{A[i-1] * A[i] * A[i+1]  +  maxCoins(A\i)} for all i in len(A)$
//
// OR, without mutating the array:
// $maxCoins(A[1..n]) = max{A[i-1] * A[i] *A[i+1]  +  maxCoins(A[1..i-1]) + maxCoins(A[i+1..n])}$
//
// Optimal Substructure:
// Suppose the i-th balloon is popped to obtain x_i coins, bringing the total coins to X.
// Then the total coins X-x_i obtained from popping the k-th balloon must be optimal too.
func maxCoins(nums []int) int {
	// dp[i][j] represents the maximum number of coins obtainable from popping balloons between
	// index i and j, inclusive.
	dp := make([][]int)
}
