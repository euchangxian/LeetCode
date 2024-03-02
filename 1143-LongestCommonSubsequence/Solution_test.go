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
		"Complex sentences with whitespace": {
			word1:    "The quick brown fox jumps over the lazy dog",
			word2:    "Lorem ipsum dolor sit amet, consectetur adipiscing elit",
			expected: 17, // "e u r  m oete adg"
		},
		"Complex sentences without whitespace": {
			word1:    "Thequickbrownfoxjumpsoverthelazydog",
			word2:    "Loremipsumdolorsitamet,consecteturadipiscingelit",
			expected: 13, // "euiconseteadg"
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

			actual = lcs(tc.word1, tc.word2)
			assert.Equal(t, tc.expected, actual)
		})
	}
}

func BenchmarkLongestCommonSubsequence(b *testing.B) {
	for i := 0; i < b.N; i++ {
		longestCommonSubsequence("The quick brown fox jumps over the lazy dog", "Lorem ipsum dolor sit amet, consectetur adipiscing elit")
	}
}
