package lc605

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestCanPlaceFlowers(t *testing.T) {
	testCases := map[string]struct {
		flowerbed  []int
		newFlowers int
		expected   bool
	}{
		"Can plant 1 flower": {
			flowerbed:  []int{1, 0, 0, 0, 1},
			newFlowers: 1,
			expected:   true,
		},
		"Cannot plant 2 flowers": {
			flowerbed:  []int{1, 0, 0, 0, 1},
			newFlowers: 2,
			expected:   false,
		},
		"Cannot plant 2 flowers, need to check next flower": {
			flowerbed:  []int{1, 0, 0, 0, 0, 1},
			newFlowers: 2,
			expected:   false,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := CanPlaceFlowers(tc.flowerbed, tc.newFlowers)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
