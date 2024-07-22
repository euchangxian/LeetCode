package lc2830

import (
	"slices"
)

// Returns the maximum amount of gold that the salesman can earn from selling the houses.
// n represents the number of houses, from house 0 to house n-1. Houses are labelled and distinct.
// offers[i] = {start_i, end_i, gold_i}, start_i and end_i inclusive.
//
// Recursive Formula (Naive approach):
// Define profit(houses[0..n-1], offers[0..m-1]) that returns the maximum amount of gold.
// houses[i] represents the i-th house, while offers[j] represents the j-th offer.
//
// Base Case:
// One buyer remaining. Check if the remaining houses fall within the offered [start, end].
//
// Recurse on each offer[j] - Two choices: Take the offer, or not.
//  1. Take the offer:
//     Reduce the range of houses and remove offer[j]. Recurse on the remaining houses.
//  2. Dont take the offer:
//     Remove offer[j], recurse on remaining houses.
//
// As such,
//
//	profit(houses[0..n-1], offers[0..m-1]) = max{profit(houses[0..n-1]\houses[start_i, end_i], offers[0..m-1]\offers[i]),
//	                                            profit(houses[0..n-1], offers[0..m-1]\offers[i])}
//	 Since there are m offers, and 2 choices each, the running time is upper bounded by O(2^n).
//
// Optimal Substructure:
// Suppose the j-th offer is taken. Then the maximum profit attainable by selling [0..n-1] houses
// with [0..m-1] buyers is the maximum profit attainable by selling [0..n-1]\[start_j, end_j] houses with
// [0..m-1]\[j] buyers.
//
// Define dp[n] such that dp[i] returns the maximum profit attainable by selling the first i houses.
func maximizeTheProfit(n int, offers [][]int) int {
	slices.SortFunc(offers, func(offer1 []int, offer2 []int) int {
		return offer1[1] - offer2[1]
	})

	j := 0 // j-th offer
	dp := make([]int, n)

	for i := 0; i < n; i++ {
		for j < len(offers) {
			// Loop through all offers that end at the i-th house.
			start, end, gold := offers[j][0], offers[j][1], offers[j][2]
			if end > i {
				break
			}
			if start-1 < 0 {
				// Handle the case when start includes the 0-th house
				dp[i] = max(dp[i], gold)
			} else {
				dp[i] = max(dp[i], dp[start-1]+gold)
			}
			j++
		}
		dp[i] = max(dp[i], dp[max(i-1, 0)])
	}
	return dp[n-1]
}
