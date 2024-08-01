package lc55

import lc45 "gitlab.com/euchangxian/leetcode/Go/0045-JumpGame"

// lc45.Jump returns the minimum number of jumps required to reach the last index. 0 represents impossible to reach the last index
// As such, we can reduce the optimization problem: find the minimum number of jumps to reach the last index, to a
// decision problem: is it possible to reach the last index in k jumps.
func canJump(nums []int) bool {
	return lc45.Jump(nums) > 0
}
