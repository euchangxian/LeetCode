package lc605

func CanPlaceFlowers(flowerbed []int, n int) bool {
	isAdjacent := false
	for _, pot := range flowerbed {
		if hasFlower(pot) {
			if isAdjacent {
				n++ // Previous flower was invalid
			}
			isAdjacent = true
			continue
		}
		if isAdjacent {
			isAdjacent = false
			continue
		}
		isAdjacent = true
		n--
	}

	return n <= 0
}

func hasFlower(pot int) bool {
	return pot == 1
}
