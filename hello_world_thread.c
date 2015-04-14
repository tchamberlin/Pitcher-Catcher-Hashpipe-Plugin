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
#include "hello_world_databuf.h"

static void *run(hashpipe_thread_args_t * args)
{
// 	paper_input_databuf_zt *db = (paper_input_databuf_t *)args->obuf;
	hashpipe_status_t st = args->st;
	const char * status_key = args->thread_desc->skey;

// 	int rv;
// 	uint64_t mcnt = 0;
//     uint64_t *data;
//     int m,f,t,c;
// 	int block_idx = 0;
	
	while (run_threads())
	{
		fprintf(stderr, "Hello, world!\n");
		sleep(1);

		hashpipe_status_lock_safe(&st);
        hputs(st.buf, status_key, "waiting");
        hashpipe_status_unlock_safe(&st);


		

// 		while ((rv=paper_input_databuf_wait_free(db, block_idx))
//                 != HASHPIPE_OK)
// 		{
//             if (rv==HASHPIPE_TIMEOUT) {
//                 hashpipe_status_lock_safe(&st);
//                 hputs(st.buf, status_key, "blocked");
//                 hashpipe_status_unlock_safe(&st);
//                 continue;
//             } else {
//                 hashpipe_error(__FUNCTION__, "error waiting for free databuf");
//                 pthread_exit(NULL);
//                 break;
//             }
//         }
// 
// 
// 		hashpipe_status_lock_safe(&st);
// 		hputs(st.buf, status_key, "receiving");
// 		hputi4(st.buf, "NETBKOUT", block_idx);
// 		hashpipe_status_unlock_safe(&st);
// 
// 		int i;
// 		// Fill in sub-block headers
// 		for(i=0; i<N_SUB_BLOCKS_PER_INPUT_BLOCK; i++) {
// 			db->block[block_idx].header.good_data = 1;
// 			db->block[block_idx].header.mcnt = mcnt;
// 			mcnt+=Nm;
// 		}
	}
	
	return NULL;
}

static hashpipe_thread_desc_t hello_world_thread = {
    name: "hello_world_thread",
    skey: "HELLSTAT",
    init: NULL,
    run:  run,
    ibuf_desc: {NULL},
    obuf_desc: {paper_input_databuf_create}
};

static __attribute__((constructor)) void ctor()
{
  register_hashpipe_thread(&hello_world_thread);
}