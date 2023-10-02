#pragma once 

enum error_codes
{   
    RETURN_OK           = 0,
    ERR_INV_CACHE_SIZE  = -1,
    ERR_INV_PAGE_L_SIZE = -2,
};


int get_input(int& cache_size, int& page_list_size);
LRU_cache fill_cache(const LRU_cache& LRU_ref);
// void print_page_list(std::list<std::string> const &list);
