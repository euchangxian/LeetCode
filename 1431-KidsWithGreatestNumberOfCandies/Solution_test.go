package lc1431

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestKidsWithCandies(t *testing.T) {
	testCases := map[string]struct {
		candies      []int
		expected     []bool
		extraCandies int
	}{
		"Mostly greater": {
			candies:      []int{2, 3, 5, 1, 3},
			extraCandies: 3,
			expected:     []bool{true, true, true, false, true},
		},
		"Only highest element is greater": {
			candies:      []int{4, 2, 1, 1, 2},
			extraCandies: 1,
			expected:     []bool{true, false, false, false, false},
		},
		"Multiple highest element": {
			candies:      []int{12, 1, 12},
			extraCandies: 10,
			expected:     []bool{true, false, true},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := KidsWithCandies(tc.candies, tc.extraCandies)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
