#include "interface.hh"

unsigned int degree = 1;
unsigned int prefetches = 0;
unsigned int useful = 0;
unsigned int counter = 10;

void prefetch_init(void) {
	
}

void prefetch_access(AccessStat stat) {
	Addr addr = stat.mem_addr;

	if (get_prefetch_bit(addr)) {
		useful++;
		clear_prefetch_bit(addr);
	}

	if (prefetches == counter) {
		if (useful > 6) {
			degree += 1;
		}
		else if(useful < 3) {
			if (degree > 1) {
				degree -= 1;
			}
		}
		prefetches = 0;
		useful = 0;
	}
	else {
		prefetches++;
	}

	for (int i = 1; i <= degree; i++) {
		addr += BLOCK_SIZE;
		if (!in_cache(addr) && !in_mshr_queue(addr))
			issue_prefetch(addr);
	}
}

void prefetch_complete(Addr addr) {
	set_prefetch_bit(addr);
}