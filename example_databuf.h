#ifndef _PAPER_DATABUF_H
#define _PAPER_DATABUF_H

#include <stdint.h>
#include "hashpipe_databuf.h"
#include "config.h"
#define CACHE_ALIGNMENT 128

#define NUM_BLOCKS 2

typedef struct example_databuf_block {
  int counter;
  int one;
  int two;
  int three;
  int four;
  int five;
  int six[6];
} example_databuf_block_t;

typedef struct example_databuf {
	hashpipe_databuf_t header;
	example_databuf_block_t block[NUM_BLOCKS];
} example_databuf_t;


/*
 * OUTPUT BUFFER FUNCTIONS
 */

hashpipe_databuf_t *example_databuf_create(int instance_id, int databuf_id);

static inline void example_databuf_clear(example_databuf_t *d)
{
    hashpipe_databuf_clear((hashpipe_databuf_t *)d);
}

static inline example_databuf_t *example_databuf_attach(int instance_id, int databuf_id)
{
    return (example_databuf_t *)hashpipe_databuf_attach(instance_id, databuf_id);
}

static inline int example_databuf_detach(example_databuf_t *d)
{
    return hashpipe_databuf_detach((hashpipe_databuf_t *)d);
}

static inline int example_databuf_block_status(example_databuf_t *d, int block_id)
{
    return hashpipe_databuf_block_status((hashpipe_databuf_t *)d, block_id);
}

static inline int example_databuf_total_status(example_databuf_t *d)
{
    return hashpipe_databuf_total_status((hashpipe_databuf_t *)d);
}

static inline int example_databuf_wait_free(example_databuf_t *d, int block_id)
{
    return hashpipe_databuf_wait_free((hashpipe_databuf_t *)d, block_id);
}

static inline int example_databuf_busywait_free(example_databuf_t *d, int block_id)
{
    return hashpipe_databuf_busywait_free((hashpipe_databuf_t *)d, block_id);
}

static inline int example_databuf_wait_filled(example_databuf_t *d, int block_id)
{
    return hashpipe_databuf_wait_filled((hashpipe_databuf_t *)d, block_id);
}

static inline int example_databuf_busywait_filled(example_databuf_t *d, int block_id)
{
    return hashpipe_databuf_busywait_filled((hashpipe_databuf_t *)d, block_id);
}

static inline int example_databuf_set_free(example_databuf_t *d, int block_id)
{
    return hashpipe_databuf_set_free((hashpipe_databuf_t *)d, block_id);
}

static inline int example_databuf_set_filled(example_databuf_t *d, int block_id)
{
    return hashpipe_databuf_set_filled((hashpipe_databuf_t *)d, block_id);
}

#endif // _PAPER_DATABUF_H
