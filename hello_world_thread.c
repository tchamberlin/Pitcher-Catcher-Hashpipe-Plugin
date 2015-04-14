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

static void *run(hashpipe_thread_args_t * args)
{
	while (run_threads())
	{
		fprintf(stderr, "Hello, world!\n");
		sleep(1);
	}
	
	return NULL;
}

static hashpipe_thread_desc_t hello_world_thread = {
    name: "hello_world_thread",
    skey: "HELLSTAT",
    init: NULL,
    run:  run,
    ibuf_desc: {NULL},
    obuf_desc: {NULL}
};

static __attribute__((constructor)) void ctor()
{
  register_hashpipe_thread(&hello_world_thread);
}