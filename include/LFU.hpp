#pragma once 

#include <iostream>
#include <unordered_map>
#include <list>
#include <array>

#define DEBUG

typedef int elem_type; // The type of element for which LFU cache was made
typedef std::list<elem_type> list;
const int POISON = 0xDEAD;


typedef struct Cache_elem
{
    size_t num_of_calls_;  // This value stores how many times element was in the flow before
    elem_type elem_value_; // This value stores the value of variable
}Cache_elem;

typedef struct LFU_cache
{
    size_t cache_size_;
    size_t page_list_size_; 
    std::list<elem_type> page_list_;

    LFU_cache(const int& cache_size, const int& page_list_size, const list& page_list);
    void print_LFU();
    ~LFU_cache();
    
}LFU_cache;  

