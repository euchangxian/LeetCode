package lc42

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestTrap(t *testing.T) {
	testCases := map[string]struct {
		height   []int
		expected int
	}{
		"TODO 1": {
			height:   []int{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1},
			expected: 6,
		},
		"TODO 2": {
			height:   []int{4, 2, 0, 3, 2, 5},
			expected: 9,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			// t.Parallel()
			actual := trap(tc.height)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
