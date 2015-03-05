#include "interface.hh"

unsigned short degree = 1;
unsigned short total_prefetches = 0;
unsigned short good_prefetches = 0;
unsigned short counter = 5;

void prefetch_init(void) {
    
}

void prefetch_access(AccessStat stat) {
    Addr addr = stat.mem_addr;

    if (get_prefetch_bit(addr)) {
        good_prefetches++;
        clear_prefetch_bit(addr);
    }

    if (total_prefetches == counter) {
		if (good_prefetches >= 4) {
			degree += 2;
		}
		else if (good_prefetches >= 2) {
			degree += 1;
		}
		else if (good_prefetches == 0){
			if (degree > 1)
				degree -= 1;
		}
        total_prefetches = 0;
        good_prefetches = 0;
    }
    else {
        total_prefetches++;
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
