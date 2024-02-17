package lc1768

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMergeAlternately(t *testing.T) {
	testCases := map[string]struct {
		word1    string
		word2    string
		expected string
	}{
		"Equal Length": {
			word1:    "abc",
			word2:    "pqr",
			expected: "apbqcr",
		},
		"word2 is longer": {
			word1:    "ab",
			word2:    "pqrs",
			expected: "apbqrs",
		},
		"word1 is longer": {
			word1:    "abcd",
			word2:    "pq",
			expected: "apbqcd",
		},
	}

	for name, tc := range testCases {
		// Capture loop variables
		name := name
		tc := tc
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := MergeAlternately(tc.word1, tc.word2)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
