package lc122

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMaxProfit(t *testing.T) {
	testCases := map[string]struct {
		prices   []int
		expected int
	}{
		"Buy and sell twice - day 2, day 3 and day 4, day 5": {
			prices:   []int{7, 1, 5, 3, 6, 4},
			expected: 7,
		},
		"Non-decreasing prices - buy once on day 1, sell on day 5": {
			prices:   []int{1, 2, 3, 4, 5},
			expected: 4,
		},
		"Non-increasing prices - never buy": {
			prices:   []int{7, 6, 4, 3, 1},
			expected: 0,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := maxProfit(tc.prices)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
