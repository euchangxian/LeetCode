package lc64

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMinPathSum(t *testing.T) {
	testCases := map[string]struct {
		grid     [][]int
		expected int
	}{
		"3x3 grid": {
			grid: [][]int{
				{1, 3, 1},
				{1, 5, 1},
				{4, 2, 1},
			},
			expected: 7,
		},
		"2x3 grid": {
			grid: [][]int{
				{1, 2, 3},
				{4, 5, 6},
			},
			expected: 12,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := minPathSum(tc.grid)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
