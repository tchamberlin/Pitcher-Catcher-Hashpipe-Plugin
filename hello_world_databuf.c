/* hello_world_databuf.c
 *
 * Routines for creating and accessing main data transfer
 * buffer in shared memory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include <time.h>

#include "hello_world_databuf.h"

hashpipe_databuf_t *hello_world_output_databuf_create(int instance_id, int databuf_id)
{
    /* Calc databuf sizes */
    size_t header_size = sizeof(hashpipe_databuf_t)
                       + sizeof(hashpipe_databuf_cache_alignment);
    size_t block_size  = sizeof(hello_world_output_block_t);
    int    n_block = 8;

    return hashpipe_databuf_create(
        instance_id, databuf_id, header_size, block_size, n_block);
}
