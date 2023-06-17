#ifndef HASH_TABLE_H
#define HASH_TABLE_H


typedef struct bucket{
    unsigned int bucket_len;
    unsigned int* data;
};

typedef struct hash_table{
    bucket* buckets;
    unsigned int buckets_amount;
    unsigned int bucket_size;
};

hash_table init_hash_table(unsigned int buckets_amount, unsigned int bucket_size);
void destroy_hash_table(hash_table* tbl);

void add_item(hash_table* tbl, unsigned int itm);
bool has_item(hash_table* tbl, unsigned int itm);

#endif