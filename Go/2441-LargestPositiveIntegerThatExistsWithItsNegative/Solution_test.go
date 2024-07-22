package lc2441

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestFindMaxK(t *testing.T) {
	testCases := map[string]struct {
		nums     []int
		expected int
	}{
		"Only one pair of matching positive and negative integer": {
			nums:     []int{-1, 2, -3, 3},
			expected: 3,
		},
		"Multiple matching integers, choose largest": {
			nums:     []int{-1, 10, 6, 7, -7, 1},
			expected: 7,
		},
		"No matching": {
			nums:     []int{-10, 8, 6, 7, -2, -3},
			expected: -1,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := findMaxK(tc.nums)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
