package lc1143

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestLongestCommonSubsequence(t *testing.T) {
	testCases := map[string]struct {
		word1    string
		word2    string
		expected int
	}{
		"Not contiguous subsequence": {
			word1:    "abcde",
			word2:    "ace",
			expected: 3,
		},
		"word1 == word2: LCS is word1/word2": {
			word1:    "abc",
			word2:    "abc",
			expected: 3,
		},
		"No common subsequence": {
			word1:    "abc",
			word2:    "def",
			expected: 0,
		},
	}

	for name, tc := range testCases {
		// Capture loop variables
		name := name
		tc := tc
		t.Run(name, func(t *testing.T) {
			t.Parallel()
			actual := longestCommonSubsequence(tc.word1, tc.word2)
			assert.Equal(t, tc.expected, actual)
		})
	}
}
