package lc62

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestUniquePaths(t *testing.T) {
	testCases := map[string]struct {
		m        int
		n        int
		expected int
	}{
		"3x2 grid ": {
			m:        3,
			n:        2,
			expected: 3,
		},
		"3x7 grid": {
			m:        3,
			n:        7,
			expected: 28,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := uniquePaths(tc.m, tc.n)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
