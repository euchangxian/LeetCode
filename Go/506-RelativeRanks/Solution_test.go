package lc506

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestFindRelativeRanks(t *testing.T) {
	testCases := map[string]struct {
		score    []int
		expected []string
	}{
		"Input array sorted in decreasing order": {
			score:    []int{5, 4, 3, 2, 1},
			expected: []string{"Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"},
		},
		"Unsorted array": {
			score:    []int{10, 3, 8, 9, 4},
			expected: []string{"Gold Medal", "5", "Bronze Medal", "Silver Medal", "4"},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := findRelativeRanks(tc.score)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
