package lc1884

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestTwoEggDrop(t *testing.T) {
	testCases := map[string]struct {
		n        int
		expected int
	}{
		"2 floors": {
			n:        2,
			expected: 2,
		},
		"100 floors": {
			n:        100,
			expected: 14,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := twoEggDrop(tc.n)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
