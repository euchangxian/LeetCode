package lc120

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMinimumTotal(t *testing.T) {
	testCases := map[string]struct {
		triangle [][]int
		expected int
	}{
		"Test Case 1": {
			triangle: [][]int{
				{2},
				{3, 4},
				{6, 5, 7},
				{4, 1, 8, 3},
			},
			expected: 11,
		},
		"Test Case 2": {
			triangle: [][]int{
				{-10},
			},
			expected: -10,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := minimumTotal(tc.triangle)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
