#include <stdio.h>
#include <stdlib.h>
#include "entropy_pool.h"

void entropy_pool_init(entropy_pool* pool) {
    mpz_init_set_ui(pool->pool_bits, 0u);
    pool->bit_count = 0u;
    pool->max_bit_count = 8u;
}

entropy_pool* get_global_entropy_pool() {
    static entropy_pool* global_pool = NULL;

    if (global_pool == NULL) {
        global_pool = malloc(sizeof(entropy_pool));
        entropy_pool_init(global_pool);
    }

    return global_pool;
}

void entropy_pool_insert_bit(entropy_pool* pool, unsigned char bit) {
    if (pool->bit_count < pool->max_bit_count) {
        unsigned actual_bit = bit  & 1;
        mpz_mul_ui(pool->pool_bits, pool->pool_bits, 2);
        mpz_add_ui(pool->pool_bits, pool->pool_bits, actual_bit);
        pool->bit_count++;
    }
}

unsigned char* entropy_pool_dump_bits(entropy_pool* pool) {
    unsigned char* result = malloc(sizeof(unsigned char)*(pool->bit_count/8));
    mpz_export(result, NULL, 1, sizeof(unsigned char), 1, 0, pool->pool_bits);
    return result;
}

bool entropy_pool_is_full(entropy_pool* pool) {
    return pool->bit_count == pool->max_bit_count;
}

void entropy_pool_set_capacity(entropy_pool* pool, unsigned bit_count) {
    pool->max_bit_count = bit_count;
}

void entropy_pool_dump_to_file(entropy_pool* pool, const char* filename) {
    FILE* dump = fopen(filename, "w");
    unsigned char* pool_bits = entropy_pool_dump_bits(pool);
    unsigned i;
    for (i = 0; i < pool->bit_count/8; i++) {
        fprintf(dump, "%c", pool_bits[i]);
    }

    fclose(dump);
}
