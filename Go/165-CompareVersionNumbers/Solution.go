package lc165

import (
	"strconv"
	"strings"
)

func compareVersion(version1 string, version2 string) int {
	revisions1 := strings.Split(version1, ".")
	revisions2 := strings.Split(version2, ".")

	// Compare common revisions first i.e up till min(len(revisions1), len(revisions2)). If equal till then,
	// then check version2 if it has revisions > 0
	for i := 0; i < min(len(revisions1), len(revisions2)); i++ {
		// Errors ignored since there will only be integer strings.
		ithRevision1, _ := strconv.ParseUint(revisions1[i], 10, 32)
		ithRevision2, _ := strconv.ParseUint(revisions2[i], 10, 32)

		if ithRevision1 == ithRevision2 {
			continue
		}
		if ithRevision1 < ithRevision2 {
			return -1
		}
		if ithRevision1 > ithRevision2 {
			return 1
		}
	}

	if len(revisions1) > len(revisions2) {
		for i := len(revisions2); i < len(revisions1); i++ {
			ithRevision1, _ := strconv.ParseUint(revisions1[i], 10, 32)
			if ithRevision1 > 0 {
				return 1
			}
		}
	}
	if len(revisions2) > len(revisions1) {
		for i := len(revisions1); i < len(revisions2); i++ {
			ithRevision2, _ := strconv.ParseUint(revisions2[i], 10, 32)
			if ithRevision2 > 0 {
				return -1
			}
		}
	}
	return 0
}
