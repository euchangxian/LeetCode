package lc70

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func Test(t *testing.T) {
	testCases := map[string]struct {
		input    int
		expected int
	}{
		"Two steps - two ways": {
			input:    2,
			expected: 2,
		},
		"Three steps - three ways": {
			input:    3,
			expected: 3,
		},
		"Four steps - five ways": {
			input:    4,
			expected: 5,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := climbStairs(tc.input)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
