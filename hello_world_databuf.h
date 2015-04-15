#ifndef _PAPER_DATABUF_H
#define _PAPER_DATABUF_H

#include <stdint.h>
#include "hashpipe_databuf.h"
#include "config.h"

#define CACHE_ALIGNMENT (128)

// Used to pad after hashpipe_databuf_t to maintain cache alignment
typedef uint8_t hashpipe_databuf_cache_alignment[
  CACHE_ALIGNMENT - (sizeof(hashpipe_databuf_t)%CACHE_ALIGNMENT)
];

/*
 * OUTPUT BUFFER STRUCTURES
 */

// #define N_OUTPUT_BLOCKS 2

typedef struct hello_world_output_header {
  uint64_t potato;
  uint64_t butterscotch;
} hello_world_output_header_t;

typedef uint8_t hello_world_output_header_cache_alignment[
  CACHE_ALIGNMENT - (sizeof(hello_world_output_header_t)%CACHE_ALIGNMENT)
];

typedef struct hello_world_output_block {
  hello_world_output_header_t header;
  hello_world_output_header_cache_alignment padding; // Maintain cache alignment
  uint64_t data[8];
} hello_world_output_block_t;

typedef struct hello_world_output_databuf {
  hashpipe_databuf_t header;
  hashpipe_databuf_cache_alignment padding; // Maintain cache alignment
  hello_world_output_block_t block[8];
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
