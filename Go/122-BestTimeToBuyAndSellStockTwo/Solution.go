package lc122

// Differs from 121-BestTimeToBuyAndSellStock. 122 allows purchasing and selling of the
// stock multiple times on same/different days
func maxProfit(prices []int) int {
	if len(prices) <= 1 {
		return 0
	}

	maxProfit := 0
	// Simply loop through, "buying" a stock on the (i-1)-th day, and "selling" it on the i-th day
	// if price[i] > price[i - 1]. Visualize this with the positive slope of a graph.
	for i := 1; i < len(prices); i++ {
		if prices[i] > prices[i-1] {
			maxProfit += prices[i] - prices[i-1]
		}
	}

	return maxProfit
}
