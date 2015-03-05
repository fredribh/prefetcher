#include "interface.hh"

Addr prev_addr;
Addr curr_addr;
Addr prefetch_addr;
unsigned int degree = 1;

void prefetch_init(void) {
	
}

void prefetch_access(AccessStat stat) {
	curr_addr = stat.mem_addr;
	
	if (prev_addr != NULL) {
		if (curr_addr == (prev_addr + BLOCK_SIZE)) {
			degree += 1;
		}
		else {
			degree = 1;
		}
	}
	
	prefetch_addr = curr_addr;
	for (int i = 1; i <= degree; i++) {
		prefetch_addr += BLOCK_SIZE;
		if (!in_cache(prefetch_addr) && !in_mshr_queue(prefetch_addr))
			issue_prefetch(prefetch_addr);
	}
	
	prev_addr = curr_addr;
}

void prefetch_complete(Addr addr) {
	
}