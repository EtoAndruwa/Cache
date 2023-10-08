#ifndef CACHE_FUNCS_HPP_TIM_A_D
#define CACHE_FUNCS_HPP_TIM_A_D

#include "LFU.hpp"

int get_input(int& cache_size, int& page_list_size, std::fstream& file_ref);
int get_page_list(Page_list& page_list, const int& page_list_size, std::fstream& file_ref); 

void print_page_list(const Page_list& page_list);
int get_cache(LFU_cache& LFU_cache_ref);
// int bubble_sort(Cache_elem* cache_ptr, const size_t& cache_size);
int comparator_cache_val(const void* a_val, const void* b_val);
int get_cache(LFU_cache& LFU_cache_ref, Page_list& page_list);
int comparator_bsearch_val(const void* a_val, const void* b_val);
int comparator_cache_freq(const void* a_val, const void* b_val);
int comparator_bsearch_freq(const void* a_val, const void* b_val); // ok;
int get_cache_old(LFU_cache& LFU_cache_ref, Page_list& page_list);

void clear_cache(LFU_cache& LFU_cache_ref);


int get_cache_on_map();

template<typename K, typename V>
void print_map(std::unordered_map<K, V> const &m);

#endif
