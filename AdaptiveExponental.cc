/*
 * A sample prefetcher which does sequential one-block lookahead.
 * This means that the prefetcher fetches the next block _after_ the one that
 * was just accessed. It also ignores requests to blocks already in the cache.
 */
#include "interface.hh"
void prefetch_init(void)
{
	/* Called before any calls to prefetch_access. */
	/* This is the place to initialize data structures. */
	Addr prev_addr;
	Addr curr_addr;
	int degree_of_prefetch = 2;
}
void prefetch_access(AccessStat stat)
{
	/* pf_addr is now an address within the _next_ cache block */
	Addr pf_addr = stat.mem_addr; //+ BLOCK_SIZE
	curr_addr = pf_addr;
	/*
	 * Issue a prefetch request if a demand miss occured,
	 * and the block is not already in cache.
	 */
	if (stat.miss && !in_cache(pf_addr)) {
		issue_prefetch(pf_addr + BLOCK_SIZE);
	}
	else {
		if (curr_addr == (prev_addr + BLOCK_SIZE)) {
			degree_of_prefetch *= 2;
			for (int i=1; i<degree_of_prefetch; i++) {
				issue_prefetch(curr_addr + i*BLOCK_SIZE);
			}
		}
		else {
			degree_of_prefetch = 2;
			for (int i=1; i<degree_of_prefetch; i++) {
				issue_prefetch(curr_addr + i*BLOCK_SIZE);
			}
		}
	}
	prev_addr = curr_addr;
}
void prefetch_complete(Addr addr) {
	/*
	 * Called when a block requested by the prefetcher has been loaded.
	 */
}
