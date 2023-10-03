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

class LFU_cache
{   
    public:
        LFU_cache(const int& cache_size, const int& page_list_size, const list& page_list);
        ~LFU_cache();

        /**
         * Here must be 3 more from rule of 5
         * Copy constructor 
         * Copy assignment
         * Move assignment
        */

        void print_LFU() const;
        bool get_full_status() const;
        bool get_empty_status() const;
        size_t get_cache_size() const;

    private:
        class Cache_elem
        {
            /**
             * All constructor, etc as default
            */

            public:
                int num_of_calls_;     // This value stores how many times element was in the flow before
                elem_type elem_value_; // This value stores the value of variable
                int num_of_iters_;     // This value stores how many times element was in the flow before
        };

        size_t cache_size_;
        bool cache_is_full_;
        bool cache_is_empt_;
        Cache_elem* cache_ptr_;
};  

