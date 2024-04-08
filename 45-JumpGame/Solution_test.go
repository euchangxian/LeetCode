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
		"": {
			nums:     []int{2, 3, 0, 1, 4},
			expected: 2,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := jump(tc.nums)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
