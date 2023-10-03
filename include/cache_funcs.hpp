#pragma once 

enum error_codes
{   
    RETURN_OK           = 0,
    ERR_INV_CACHE_SIZE  = -1,
    ERR_INV_PAGE_L_SIZE = -2,
};

enum return_codes
{   
    VALUE_WAS_NOT_FOUND = -1,
};

int get_input(int& cache_size, int& page_list_size);
int get_page_list(Page_list& page_list, const int& page_list_size); 
void print_page_list(const Page_list& page_list);
int get_cache(LFU_cache& LFU_cache_ref);
// int bubble_sort(Cache_elem* cache_ptr, const size_t& cache_size);
int comparator_cache_val(const void* a_val, const void* b_val);
int get_cache(LFU_cache& LFU_cache_ref, Page_list& page_list);
int comparator_bsearch(const void* a_val, const void* b_val);

