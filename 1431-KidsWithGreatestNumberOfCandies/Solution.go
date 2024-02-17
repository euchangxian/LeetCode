package lc1431

import "slices"

func KidsWithCandies(candies []int, extraCandies int) []bool {
	maxCandies := slices.Max(candies)
	kidsGreater := make([]bool, len(candies))
	for i, currCandies := range candies {
		isGreater := currCandies+extraCandies >= maxCandies
		kidsGreater[i] = isGreater
	}
	return kidsGreater
}
