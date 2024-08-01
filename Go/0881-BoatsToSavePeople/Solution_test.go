package lc881

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestNumRescueBoats(t *testing.T) {
	testCases := map[string]struct {
		people   []int
		limit    int
		expected int
	}{
		"One boat is sufficient": {
			people:   []int{1, 2},
			limit:    3,
			expected: 1,
		},
		"Multiple boats needed. Not necessarily fully utilised": {
			people:   []int{1, 2, 2, 3},
			limit:    3,
			expected: 3,
		},
		"One boat for each person": {
			people:   []int{3, 5, 3, 4},
			limit:    5,
			expected: 4,
		},
		"Each boat carries at most 2 person": {
			people:   []int{1, 1, 1},
			limit:    3,
			expected: 2,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := numRescueBoats(tc.people, tc.limit)
			assert.Equal(t, tc.expected, actual)

			actual = numRescueBoatsComparisonBasedSorting(tc.people, tc.limit)
			assert.Equal(t, tc.expected, actual)
		})
	}
}

func BenchmarkNumRescueBoats(b *testing.B) {
	for i := 0; i < b.N; i++ {
		numRescueBoats([]int{89, 59, 32, 74, 81, 12, 7, 49, 43, 51, 62, 91, 27}, 100)
	}
}

func BenchmarkNumRescueBoatsComparisonBasedSorting(b *testing.B) {
	for i := 0; i < b.N; i++ {
		numRescueBoatsComparisonBasedSorting([]int{89, 59, 32, 74, 81, 12, 7, 49, 43, 51, 62, 91, 27}, 100)
	}
}
