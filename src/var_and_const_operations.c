#include "operations.h"
#include "ijvm.h"
#include "stack.h"
#include "util.h"

static bool isWide = false;

typedef struct _index_size_pair
{
    uint16_t index;
    uint16_t size;
} index_size_pair;


index_size_pair parse_index(byte_t* index){
    index_size_pair p;
    if(isWide){
        p.index = read_uint16_t(index);
        p.size = 2;
        isWide = false;
    }else{
        p.index = *index;
        p.size = 1;
    }
    return p;
}

int16_t ldc_w(uint16_t index){
    wpush(get_constant(index));
    return 3;
}

int16_t iload(byte_t* index){
    index_size_pair isp = parse_index(index);
    wpush(get_local_variable(isp.index));
    return 1 + isp.size;
}

int16_t istore(byte_t* index){
    index_size_pair isp = parse_index(index);
    set_local_var(isp.index, wpop());
    return 1 + isp.size;
}

int16_t iinc(byte_t* args){
    index_size_pair isp = parse_index(args);
    word_t var = get_local_variable(isp.index);

    int8_t inc = args[isp.size];
    set_local_var(isp.index, var + inc);
    return 2 + isp.size;
}

int16_t wide(){
    isWide = true;
    return 1;
}

