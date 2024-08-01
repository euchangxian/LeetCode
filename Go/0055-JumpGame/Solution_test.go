package lc55

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestCanJump(t *testing.T) {
	testCases := map[string]struct {
		nums     []int
		expected bool
	}{
		"All positive jump lengths": {
			nums:     []int{2, 3, 1, 1, 4},
			expected: true,
		},
		"All prefix jumps arrive at 0": {
			nums:     []int{3, 2, 1, 0, 4},
			expected: false,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := canJump(tc.nums)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
