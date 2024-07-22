package lc63

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestUniquePathsWithObstacles(t *testing.T) {
	testCases := map[string]struct {
		obstacleGrid [][]int
		expected     int
	}{
		"3x3 grid, obstacle in middle cell": {
			obstacleGrid: [][]int{
				{0, 0, 0},
				{0, 1, 0},
				{0, 0, 0},
			},
			expected: 2,
		},
		"2x2 grid, obstacle on top-right cell": {
			obstacleGrid: [][]int{
				{0, 1},
				{0, 0},
			},
			expected: 1,
		},
		"1x2 grid, obstacle on goal cell": {
			obstacleGrid: [][]int{
				{0, 1},
			},
			expected: 0,
		},
		"2x1 grid, obstacle on goal cell": {
			obstacleGrid: [][]int{
				{0},
				{1},
			},
			expected: 0,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := uniquePathsWithObstacles(tc.obstacleGrid)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
