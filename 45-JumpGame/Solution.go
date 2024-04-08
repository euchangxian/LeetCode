package lc45

// Greedy solution. O(n)
// Greedy Choice property:
// Let nums[i]* be the jump that reaches the furthest index, such that
// i + nums[i]* = max(j + nums[j]) for all 0<=j<=len(nums)
// Then, there exists an optimal solution which includes nums[i]*.
func Jump(nums []int) int {
	jumps := 1
	furthest := nums[0] // represents the current furthest index reachable with the number of jumps

	for i := 1; i < len(nums); i++ {
		if i > furthest {
			// Cannot reach the end
			return 0
		}
		if i+nums[i] > furthest {
			jumps++
			furthest = i + nums[i]
		}
		if furthest >= len(nums)-1 {
			// Can already reach last index
			break
		}
	}

	return jumps
}

// Naive DP solution. O(n^2)
func jumpNaive(nums []int) int {
	dp := make([]int, len(nums))
	// dp[i] represents the minimum number of jumps required to reach the i-th position.
	for i := 0; i < len(nums); i++ {
		dp[i] = 10000 // 0 <= nums[i] <= 1000
	}
	dp[0] = 0

	for i, jumpLength := range nums {
		for j := 1; j <= jumpLength; j++ {
			if i+j >= len(nums) {
				break
			}
			dp[i+j] = min(1+dp[i], dp[i+j])
		}
	}
	return dp[len(nums)-1]
}
