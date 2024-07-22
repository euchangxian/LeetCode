package lc3075

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMaximumHappinessSum(t *testing.T) {
	testCases := map[string]struct {
		happiness []int
		k         int
		expected  int64
	}{
		"All happiness values will still be positive after k-iterations": {
			happiness: []int{1, 2, 3},
			k:         2,
			expected:  4,
		},
		"Should not add negative happiness values": {
			happiness: []int{1, 1, 1, 1},
			k:         3,
			expected:  1,
		},
		"Pick largest happiness value": {
			happiness: []int{5},
			k:         1,
			expected:  5,
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := maximumHappinessSum(tc.happiness, tc.k)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
