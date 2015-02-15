#include "interface.hh"

void prefetch_init(void) {
	Addr prev_addr;
	Addr curr_addr;
	int degree = 1;
}

void prefetch_access(AccessStat stat) {
	curr_addr = stat.mem_addr;
	
	if (prev_addr != NULL) {
		if (curr_addr == (prev_addr + BLOCK_SIZE)) {
			degree = degree * 2;
		}
		else {
			degree = 1;
		}
	}
	
	for (i = 1; i <= degree; i++) {
		if ((!in_cache(curr_addr + (i * BLOCK_SIZE))) && (!in_mshr_queue(curr_addr + (i * BLOCK_SIZE)))) {
			issue_prefetch(curr_addr + (i * BLOCK_SIZE));
		}
	}
	
	prev_addr = curr_addr;
}

void prefetch_complete(Addr addr) {
	
}