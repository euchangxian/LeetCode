package lc45

func jump(nums []int) int {
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
