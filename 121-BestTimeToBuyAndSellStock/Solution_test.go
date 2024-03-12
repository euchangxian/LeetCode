package lc121

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMaxProfit(t *testing.T) {
	testCases := map[string]struct {
		prices   []int
		expected int
	}{
		"Buy on day 2, sell on day 5": {
			prices:   []int{7, 1, 5, 3, 6, 4},
			expected: 5,
		},
		"No transaction - non-increasing": {
			prices:   []int{7, 5, 4, 3, 1},
			expected: 0,
		},
	}

	for name, tc := range testCases {
		// Capture loop variables
		name := name
		tc := tc
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := maxProfit(tc.prices)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
