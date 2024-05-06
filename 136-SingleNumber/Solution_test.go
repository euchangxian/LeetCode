package lc136

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestSingleNumber(t *testing.T) {
	testCases := map[string]struct {
		nums     []int
		expected int
	}{
		"Trivial case": {
			nums:     []int{1},
			expected: 1,
		},
		"Multiple unique elements": {
			nums:     []int{4, 1, 2, 1, 2},
			expected: 4,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := singleNumber(tc.nums)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
