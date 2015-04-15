#ifndef _PAPER_DATABUF_H
#define _PAPER_DATABUF_H

#include <stdint.h>
#include "hashpipe_databuf.h"
#include "config.h"
#define CACHE_ALIGNMENT 128

typedef struct hello_world_output_databuf {
  hashpipe_databuf_t header;
  int one;
  int two;
  int three;
  int four;
  int five;
  int six[6];
} hello_world_output_databuf_t;

/*
 * OUTPUT BUFFER FUNCTIONS
 */

hashpipe_databuf_t *hello_world_output_databuf_create(int instance_id, int databuf_id);

static inline void hello_world_output_databuf_clear(hello_world_output_databuf_t *d)
{
    hashpipe_databuf_clear((hashpipe_databuf_t *)d);
}

static inline hello_world_output_databuf_t *hello_world_output_databuf_attach(int instance_id, int databuf_id)
{
    return (hello_world_output_databuf_t *)hashpipe_databuf_attach(instance_id, databuf_id);
}

static inline int hello_world_output_databuf_detach(hello_world_output_databuf_t *d)
{
    return hashpipe_databuf_detach((hashpipe_databuf_t *)d);
}

static inline int hello_world_output_databuf_block_status(hello_world_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_block_status((hashpipe_databuf_t *)d, block_id);
}

static inline int hello_world_output_databuf_total_status(hello_world_output_databuf_t *d)
{
    return hashpipe_databuf_total_status((hashpipe_databuf_t *)d);
}

static inline int hello_world_output_databuf_wait_free(hello_world_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_wait_free((hashpipe_databuf_t *)d, block_id);
}

static inline int hello_world_output_databuf_busywait_free(hello_world_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_busywait_free((hashpipe_databuf_t *)d, block_id);
}

static inline int hello_world_output_databuf_wait_filled(hello_world_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_wait_filled((hashpipe_databuf_t *)d, block_id);
}

static inline int hello_world_output_databuf_busywait_filled(hello_world_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_busywait_filled((hashpipe_databuf_t *)d, block_id);
}

static inline int hello_world_output_databuf_set_free(hello_world_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_set_free((hashpipe_databuf_t *)d, block_id);
}

static inline int hello_world_output_databuf_set_filled(hello_world_output_databuf_t *d, int block_id)
{
    return hashpipe_databuf_set_filled((hashpipe_databuf_t *)d, block_id);
}

#endif // _PAPER_DATABUF_H
