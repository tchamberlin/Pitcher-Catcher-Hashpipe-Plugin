#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <errno.h>

#include "hashpipe.h"
#include "example_databuf.h"

static void *run(hashpipe_thread_args_t * args)
{
	fprintf(stderr, "catcher's ibuf address: %p\n", (void *)&(*(args->ibuf)));
	example_databuf_t *db = (example_databuf_t *)args->ibuf;
	hashpipe_status_t st = args->st;
	const char * status_key = args->thread_desc->skey;

	int rv;
	int block_idx = 0;

	while (run_threads())
	{
		

		hashpipe_status_lock_safe(&st);
        hputs(st.buf, status_key, "waiting");
        hashpipe_status_unlock_safe(&st);

		while ((rv=example_databuf_wait_filled(db, block_idx)) != HASHPIPE_OK) {
              if (rv==HASHPIPE_TIMEOUT) {
                  hashpipe_status_lock_safe(&st);
                  hputs(st.buf, status_key, "blocked");
                  hashpipe_status_unlock_safe(&st);
                  continue;
              } else {
                  hashpipe_error(__FUNCTION__, "error waiting for free databuf");
                  pthread_exit(NULL);
                  break;
              }
          }

		hashpipe_status_lock_safe(&st);
		hputs(st.buf, status_key, "receiving");
		hputi4(st.buf, "NETBKOUT", block_idx);
		hashpipe_status_unlock_safe(&st);

		fprintf(stderr, "Catching!\n");
		sleep(1);

		fprintf(stderr, "one: %d\n", db->one);
		fprintf(stderr, "two: %d\n", db->two);

		// Mark block as full
        example_databuf_set_free(db, block_idx);

        // Setup for next block
//         block_idx = (block_idx + 1) % 8;
// 		fprintf(stderr, "block_idx is now: %d\n", block_idx);

        /* Will exit if thread has been cancelled */
        pthread_testcancel();
	}

	return NULL;
}

static hashpipe_thread_desc_t catcher_thread = {
    name: "catcher_thread",
    skey: "CATCSTAT",
    init: NULL,
    run:  run,
    ibuf_desc: {example_databuf_create},
    obuf_desc: {NULL}
};

static __attribute__((constructor)) void ctor()
{
  register_hashpipe_thread(&catcher_thread);
}