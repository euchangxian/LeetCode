package lc1884

// Returns the minimum number of moves to determine with certainty the critical floor f_c,
// given two eggs.
//
// An egg dropped above any floor higher than the critical floor f_c will break, while an egg
// dropped on or below the critical floor f_c will not break and can be reused.
//
// Suppose the minimum number of moves to determine f_c given two eggs is x.
// Then, the claim is that the first floor to drop the egg from cannot exceed x.
//
// Proof (by contradiction):
//  1. Suppose for the sake of contradiction that the first floor picked exceeds x. That is
//     pick x + 1.
//  2. Then, there are two possible cases:
//     2.1.   Case 1: Egg breaks
//     2.1.1. Then, for the critical floor to be found with certainty, the remaining egg has to be dropped
//     sequentially from floor 1, till floor x.
//     2.1.2. This linear search takes x steps. Combined with the 1 step from dropping the first egg at floor x + 1,
//     the total number of moves to find the critical floor is x + 1, which contradicts the claim.
//  3. Thus, given two eggs, the claim that the first floor picked cannot exceed x holds true.
//
// Generalizing it to k number of eggs, the claim is that there exists an Optimal substructure.
//
// Optimal Substructure:
// Given k eggs and n floors:
// Suppose an egg is dropped at floor x, the minimum number of moves to determine f_c
// is the minimum of the maximum (certainty i.e. worst case) between:
//  1. the minimum number of moves to deterimne f_c with (k - 1) eggs and (x - 1) floors, and (egg breaks)
//  2. the minimum number of moves to determine f_c with k eggs and (n - x) floors. (egg does not break)
//
// Suppose the minimum number of moves to determine f_c is x. Then
func twoEggDrop(n int) int {
	MAX_FLOORS := 10000
	// Initialize DP array.
	dp := make([][]int, 2)
	dp[0] = make([]int, n+1)
	dp[1] = make([]int, n+1)

	// Initialize base cases
	// 1 egg, i floors => i steps
	for i := 0; i < n+1; i++ {
		dp[0][i] = i
		// dp[1][i] = 1000000
	}
	dp[1][1] = 1 // 2 eggs, 1 floor => 1 trial/step

	// For each i number of floors
	for i := 2; i < n+1; i++ {
		dp[1][i] = MAX_FLOORS
		// try dropping at x = {1, ..., i}
		for x := 1; x < i+1; x++ {
			// dp[1][x] = min(dp[1][x], 1+max(dp[0][x-1], dp[1][i-x]))
			dp[1][i] = min(dp[1][i], 1+max(dp[0][x-1], dp[1][i-x]))
		}
	}
	return dp[1][n]
}
