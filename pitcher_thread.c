// run with:
// clean_ipc; taskset 0x0606 hashpipe -p example -I 0 -o BINDHOST=px1-2.gb.nrao.edu -o GPUDEV=0 -o XID=0 -c 3 pitcher_thread -c 2 catcher_thread


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
	fprintf(stderr, "pitcher's ibuf address: %p\n", (void *)&(*(args->obuf)));
	example_databuf_t *db = (example_databuf_t *)args->obuf;
	hashpipe_status_t st = args->st;
	const char * status_key = args->thread_desc->skey;

	int rv;
	int block_idx = 0;
	
	while (run_threads())
	{
		

		hashpipe_status_lock_safe(&st);
        hputs(st.buf, status_key, "waiting");
        hashpipe_status_unlock_safe(&st);

		while ((rv=example_databuf_wait_free(db, block_idx)) != HASHPIPE_OK) {
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
		hputs(st.buf, status_key, "sending");
		hputi4(st.buf, "NETBKOUT", block_idx);
		hashpipe_status_unlock_safe(&st);

		fprintf(stderr, "Pitching!\n");
		sleep(1);

		db->one = 1;
		db->two = 2;
		db->three = 3;
		db->four = 4;
		db->five = 5;

		int i;
		for (i = 0; i < 6; i++) {
			db->six[i] = 6;
		}

		// Mark block as full
        example_databuf_set_filled(db, block_idx);

        // Setup for next block
//         block_idx = (block_idx + 1) % 8;
// 		fprintf(stderr, "block_idx is now: %d\n", block_idx);

        /* Will exit if thread has been cancelled */
        pthread_testcancel();
	}
	
	return NULL;
}

static hashpipe_thread_desc_t pitcher_thread = {
    name: "pitcher_thread",
    skey: "PITCSTAT",
    init: NULL,
    run:  run,
    ibuf_desc: {NULL},
    obuf_desc: {example_databuf_create}
};

static __attribute__((constructor)) void ctor()
{
  register_hashpipe_thread(&pitcher_thread);
}