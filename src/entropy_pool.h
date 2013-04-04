#ifndef entropy_pool_h
#define entropy_pool_h

#include <gmp.h>
#include <stdbool.h>

typedef struct _entropy_pool {
    mpz_t pool_bits;
    unsigned bit_count;
    unsigned max_bit_count;
} entropy_pool;

entropy_pool* get_global_entropy_pool();

void entropy_pool_insert_bit(entropy_pool* pool, unsigned char bit);
unsigned char* entropy_pool_dump_bits(entropy_pool* pool);
void entropy_pool_dump_to_file(entropy_pool* pool, const char* filename);
bool entropy_pool_is_full(entropy_pool* pool);
void entropy_pool_set_capacity(entropy_pool* pool, unsigned bit_count);

#endif
