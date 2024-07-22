package lc739

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestDailyTemperatures(t *testing.T) {
	testCases := map[string]struct {
		temperatures []int
		expected     []int
	}{
		"Non-monotonic daily temperatures": {
			temperatures: []int{73, 74, 75, 71, 69, 72, 76, 73},
			expected:     []int{1, 1, 4, 2, 1, 1, 0, 0},
		},
		"Monotonically increasing daily temperatures": {
			temperatures: []int{30, 40, 50, 60},
			expected:     []int{1, 1, 1, 0},
		},
		"Small temperatures length": {
			temperatures: []int{30, 60, 90},
			expected:     []int{1, 1, 0},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := dailyTemperatures(tc.temperatures)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
