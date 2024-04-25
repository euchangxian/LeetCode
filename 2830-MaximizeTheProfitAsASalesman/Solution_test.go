package lc2830

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMaximizeTheProfit(t *testing.T) {
	testCases := map[string]struct {
		offers   [][]int
		n        int
		expected int
	}{
		"Test Case 1": {
			n: 5,
			offers: [][]int{
				{0, 0, 1},
				{0, 2, 2},
				{1, 3, 2},
			},
			expected: 3,
		},
		"Test Case 2": {
			n: 5,
			offers: [][]int{
				{0, 0, 1},
				{0, 2, 10},
				{1, 3, 2},
			},
			expected: 10,
		},
		"Test Case 3": {
			n: 4,
			offers: [][]int{
				{0, 0, 6},
				{1, 2, 8},
				{0, 3, 7},
				{2, 2, 5},
				{0, 1, 5},
				{2, 3, 2},
				{0, 2, 8},
				{2, 3, 10},
				{0, 3, 2},
			},
			expected: 16,
		},
		"Test Case 4": {
			n: 15,
			offers: [][]int{
				{5, 5, 10},
				{2, 6, 6},
				{8, 11, 5},
				{7, 11, 9},
				{2, 4, 1},
				{3, 8, 5},
				{0, 6, 9},
				{0, 10, 5},
				{5, 10, 8},
				{4, 5, 1},
			},
			expected: 20,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			// t.Parallel()
			actual := maximizeTheProfit(tc.n, tc.offers)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
