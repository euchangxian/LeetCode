package lc312

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMaxCoins(t *testing.T) {
	testCases := map[string]struct {
		nums     []int
		expected int
	}{
		"Pop 1->5->3->8": {
			nums:     []int{3, 1, 5, 8},
			expected: 167,
		},
		"Balloons can be popped in any order to attain maximum": {
			nums:     []int{1, 5},
			expected: 10,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := maxCoins(tc.nums)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
