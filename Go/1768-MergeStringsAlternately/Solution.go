package lc1768

import (
	"strings"
)

func MergeAlternately(word1 string, word2 string) string {
	i := 0
	j := 0

	var sb strings.Builder
	sb.Grow(len(word1) + len(word2))

	isOdd := true
	for i < len(word1) && j < len(word2) {
		if isOdd {
			sb.WriteByte(word1[i])
			i++
		} else {
			sb.WriteByte(word2[j])
			j++
		}
		isOdd = !isOdd
	}

	// Appends remaining characters.
	sb.WriteString(word1[i:])
	sb.WriteString(word2[j:])

	return sb.String()
}
