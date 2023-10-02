#pragma once 

enum error_codes
{   
    RETURN_OK           = 0,
    ERR_INV_CACHE_SIZE  = -1,
    ERR_INV_PAGE_L_SIZE = -2,
};


int get_input(int& cache_size, int& page_list_size);
LFU_cache fill_cache(const LFU_cache& LFU_ref);
int get_page_list(list& page_list, const int& page_list_size);
void print_page_list(const list& page_list);

