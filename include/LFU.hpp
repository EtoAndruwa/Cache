#pragma once 

#include <iostream>
#include <unordered_map>
#include <list>
#include <array>
#include <bits/stdc++.h>
#include <cstdlib>

#define DEBUG

typedef int elem_type; // The type of element for which LFU cache was made
typedef std::list<elem_type> list;

class Cache_elem
{
    /**
        * All constructor, etc as default
    */

    friend int binary_search(Cache_elem* cache_ptr, const size_t& cache_size, const elem_type& value);

    public:
        int num_of_calls_;     // This value stores how many times element was in the flow before
        elem_type elem_value_; // This value stores the value of variable
        int num_of_iters_;     // This value stores how many times element was in the flow before
};

class LFU_cache
{   
    friend int binary_search(Cache_elem* cache_ptr, const size_t& cache_size, const elem_type& value);
    friend void qsort(void *__base, size_t __nmemb, size_t __size, comparison_fn_t __compar);
    friend int get_cache(LFU_cache& LFU_cache_ref);


    public:
        LFU_cache(const int& cache_size);
        ~LFU_cache();

        /**
         * Here must be 3 more from rule of 5
         * Copy constructor 
         * Copy assignment
         * Move assignment
        */

        void print_LFU() const;
        bool get_full_status() const;
        size_t get_cache_size() const;

    private:

        size_t cache_size_;
        bool cache_is_full_;
        Cache_elem* cache_ptr_;
};  

class Page_list
{
    /**
        * All constructor, etc as default
    */
   
    public:
        list page_list_ptr_;
        size_t page_list_size_;
};