package lc452

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestFindMinArrowShots(t *testing.T) {
	testCases := map[string]struct {
		points   [][]int
		expected int
	}{
		"Unsorted, some overlapping balloons": {
			points: [][]int{
				{10, 16},
				{2, 8},
				{1, 6},
				{7, 12},
			},
			expected: 2,
		},
		"Non-overlapping balloons": {
			points: [][]int{
				{1, 2},
				{3, 4},
				{5, 6},
				{7, 8},
			},
			expected: 4,
		},
		"Sorted, some overlapping balloons": {
			points: [][]int{
				{1, 2},
				{2, 3},
				{3, 4},
				{4, 5},
			},
			expected: 2,
		},
		"Unsorted, no overlap at centre, requiring two arrows": {
			points: [][]int{
				{1, 2},
				{4, 5},
				{1, 5},
			},
			expected: 2,
		},
		"Unsorted, first balloon has large interval": {
			points: [][]int{
				{9, 12},
				{1, 10},
				{4, 11},
				{8, 12},
				{3, 9},
				{6, 9},
				{6, 7},
			},
			expected: 2,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := findMinArrowShots(tc.points)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
