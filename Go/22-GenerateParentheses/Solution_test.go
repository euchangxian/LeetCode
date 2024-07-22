package lc22

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestGenerateParenthesis(t *testing.T) {
	testCases := map[string]struct {
		pairs    int
		expected []string
	}{
		"Three pairs of parentheses": {
			pairs:    3,
			expected: []string{"((()))", "(()())", "(())()", "()(())", "()()()"},
		},
		"Two pairs of parentheses": {
			pairs:    2,
			expected: []string{"(())", "()()"},
		},
		"One pair of parentheses": {
			pairs:    1,
			expected: []string{"()"},
		},
		"Zero pairs - Base case": {
			pairs:    0,
			expected: []string{""},
		},
	}

	for name, tc := range testCases {
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := generateParenthesis(tc.pairs)
			assert.ElementsMatch(t, tc.expected, actual)
		})
	}
}
