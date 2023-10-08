#ifndef LFU_HPP_TIM_A_D
#define LFU_HPP_TIM_A_D

#include <iostream> 
#include <list>     
#include <array>
#include <bits/stdc++.h>
#include <cstdlib> 
#include <valgrind/memcheck.h>
#include <map>


enum error_codes
{   
    RETURN_OK           = 0,
    ERR_INV_CACHE_SIZE  = -1,
    ERR_INV_PAGE_L_SIZE = -2,
    ERR_NO_TEST_FILE    = -3, 

};

enum return_codes
{   
    VALUE_WAS_NOT_FOUND = -1,
};


// #define DEBUG

typedef int elem_type;             // The type of element for which LFU cache was made
typedef std::list<elem_type> list; // std::list typedef

class Cache_elem
{
    /**
        * All constructor, etc as default
    */

    friend int binary_search(Cache_elem* cache_ptr, const size_t& cache_size, const elem_type& value);

    public:
        int num_of_calls_;     // This value stores how many times element was in the flow before
        elem_type elem_value_; // This value stores the value of variable
        int num_of_iter_;     // This value stores how many times element was in the flow before
};

class LFU_cache
{   
    friend void *bsearch(const void *__key, const void *__base, size_t __nmemb, size_t __size, comparison_fn_t __compar);
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

        void print_LFU() const;                 // prints all data about LFU_cache
        bool get_full_status() const;           // get the value of cache_is_full_
        void set_full_status(const bool& val);  // get the value of cache_is_full_
        size_t get_cache_size() const;          // gets tha value of cache_size_
        Cache_elem* get_cache_ptr() const;      // get the pointer to the array of Cache_elem's
        Cache_elem** get_ptr_to_arr() const;      

    private:
        size_t cache_size_;             // stores the cache size
        bool cache_is_full_;            // stores the cache flag of being full
        Cache_elem* cache_ptr_;         // stores the pointer ot the array of Cache_elem's
        Cache_elem** array_of_ptrs_;         
};  

class Page_list
{
    /**
        * All constructor, etc as default
    */
   
    public:
        list page_list_ptr_;            // std::list typedef for list of pages
        size_t page_list_size_;         // the number of elements in the std::list
};

#endif
