/* pitcher_databuf.c
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

#include "pitcher_output_databuf.h"

hashpipe_databuf_t *pitcher_output_databuf_create(int instance_id, int databuf_id)
{
    /* Calc databuf sizes */
    size_t header_size = sizeof (hashpipe_databuf_t);
    size_t block_size  = sizeof (pitcher_output_databuf_t);
    int    n_block = NUM_BLOCKS;

    return hashpipe_databuf_create(
        instance_id, databuf_id, header_size, block_size, n_block);
}
