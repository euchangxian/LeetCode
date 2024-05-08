package lc506

import (
	"container/heap"
	"strconv"
)

func findRelativeRanks(score []int) []string {
	comparator := func(i int, j int) bool {
		return score[i] > score[j]
	}
	indices := make([]int, len(score))
	for i := range score {
		indices[i] = i
	}

	pq := &IntPriorityQueue{
		values: indices,
		comp:   comparator,
	}
	heap.Init(pq)

	ranks := make([]string, len(score))

	for i := range len(score) {
		idx := heap.Pop(pq).(int)

		switch i {
		case 0:
			ranks[idx] = "Gold Medal"
		case 1:
			ranks[idx] = "Silver Medal"
		case 2:
			ranks[idx] = "Bronze Medal"
		default:
			ranks[idx] = strconv.Itoa(i + 1)
		}
	}
	return ranks
}

type IntPriorityQueue struct {
	values []int
	comp   func(i int, j int) bool
}

func (pq IntPriorityQueue) Len() int {
	return len(pq.values)
}

func (pq IntPriorityQueue) Less(i int, j int) bool {
	return pq.comp(pq.values[i], pq.values[j])
}

func (pq IntPriorityQueue) Swap(i int, j int) {
	pq.values[i], pq.values[j] = pq.values[j], pq.values[i]
}

func (pq *IntPriorityQueue) Push(x any) {
	pq.values = append(pq.values, x.(int))
}

func (pq *IntPriorityQueue) Pop() any {
	old := pq.values
	n := len(old)
	item := old[n-1]
	pq.values = old[0 : n-1]
	return item
}
