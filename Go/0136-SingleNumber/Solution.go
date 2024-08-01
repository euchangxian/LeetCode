package lc136

// Find the number that occurs only once in the nums array, where every other number occurs twice.
// Uses XOR, where a XOR a = 0, and 0 XOR a = a.
func singleNumber(nums []int) int {
	single := 0

	for _, num := range nums {
		single ^= num
	}
	return single
}
