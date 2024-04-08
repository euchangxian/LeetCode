package lc45

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestJump(t *testing.T) {
	testCases := map[string]struct {
		nums     []int
		expected int
	}{
		"Jump to nums[1] instead of nums[2], then to nums[4] i.e. last index": {
			nums:     []int{2, 3, 1, 1, 4},
			expected: 2,
		},
		"Impossible to reach last index": {
			nums:     []int{3, 2, 1, 0, 1, 4},
			expected: 0,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := Jump(tc.nums)
			assert.Equal(t, tc.expected, actual)
		})
	}
}

func BenchmarkGreedyJump(b *testing.B) {
	for i := 0; i < b.N; i++ {
		Jump([]int{2, 3, 1, 1, 4, 5, 2, 1, 3, 2, 4})
	}
}

func BenchmarkNaiveJump(b *testing.B) {
	for i := 0; i < b.N; i++ {
		jumpNaive([]int{2, 3, 1, 1, 4, 5, 2, 1, 3, 2, 4})
	}
}
