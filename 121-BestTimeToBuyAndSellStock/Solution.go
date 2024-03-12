package lc121

func maxProfit(prices []int) int {
	if len(prices) <= 1 {
		return 0
	}

	currMax := 0 // 0 <= prices[i] <= 10^4

	i := 0 // left pointer
	for j := 1; j < len(prices); j++ {
		if prices[j] < prices[i] {
			i = j
		}
		currMax = max(currMax, prices[j]-prices[i])
	}

	return currMax
}
