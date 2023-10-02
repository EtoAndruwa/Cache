#pragma once 

#include <iostream>
#include <unordered_map>
#include <list>

#define DEBUG

typedef int elem_type; // The type of element for which LRU cache was made
typedef std::list<elem_type> list;


class Cache_elem
{
    public: 
        Cache_elem();
        ~Cache_elem();
        // Cache_elem& operator=(const Cache_elem& rhs);
    private:
        size_t num_of_calls_;  // This value stores how many times element was in the flow before
        elem_type elem_value_; // This value stores the value of variable
};

class LRU_cache
{
    public: 
        LRU_cache();
        ~LRU_cache();
        // LRU_cache& operator=(const LRU_cache& rhs);

    private: 
        size_t cache_size_;
        size_t page_list_size_; 
        std::list<elem_type> page_list_;

};  


