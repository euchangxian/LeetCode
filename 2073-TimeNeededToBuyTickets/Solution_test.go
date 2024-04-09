package lc2073

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestTimeRequiredToBuy(t *testing.T) {
	testCases := map[string]struct {
		tickets  []int
		k        int
		expected int
	}{
		"Every person at index i != k has at least tickets[k] number of tickets": {
			tickets:  []int{2, 3, 2},
			k:        2,
			expected: 6,
		},
		"After one round, only person k has tickets to buy": {
			tickets:  []int{5, 1, 1, 1},
			k:        0,
			expected: 8,
		},
		"People behind person k with more tickets are not considered for the last round": {
			tickets:  []int{84, 49, 5, 24, 70, 77, 87, 8},
			k:        3,
			expected: 154, // naive answer will be adding min(tickets[i], 24) for each i, resulting in 157.
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := timeRequiredToBuy(tc.tickets, tc.k)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
