package lc2073

func timeRequiredToBuy(tickets []int, k int) int {
	timeRequired := 0

	for i, numTickets := range tickets {
		ticketsToBuy := tickets[k]
		if i > k && numTickets >= ticketsToBuy {
			// For the last round, no need to consider these people,
			// since person k will have finished buying
			ticketsToBuy = tickets[k] - 1
		}
		timeRequired += min(numTickets, ticketsToBuy)
	}
	return timeRequired
}
