package lc72

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMinDistance(t *testing.T) {
	testCases := map[string]struct {
		word1    string
		word2    string
		expected int
	}{
		"All removals": {
			word1:    "horse",
			word2:    "rse",
			expected: 2,
		},
		"Replace('h', 'r')->remove('r')->remove('e')": {
			word1:    "horse",
			word2:    "ros",
			expected: 3,
		},
    "Mix of insert, delete and replace operations": {
      word1: "intention",
      word2: "execution",
      expected: 5,
    }
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := minDistance(tc.grid)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
