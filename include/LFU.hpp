#ifndef LFU_HPP_TIM_A_D
#define LFU_HPP_TIM_A_D

/*==========================================================================================================================================*/

#include <iostream> 
#include <list>     
#include <valgrind/memcheck.h>
#include <unordered_map>
#include <algorithm>

/*==========================================================================================================================================*/

#define DEBUG

typedef int elem_type;             // The type of element for which LFU cache was made
typedef std::list<elem_type> list; // std::list typedef
class Page_list;

/*==========================================================================================================================================*/

enum error_codes
{
    RETURN_OK,
};

/*==========================================================================================================================================*/

class Cache_elem
{
    /**
        * All constructor, etc as default
    */

    private:
        elem_type elem_value_;      // This value stores the value of variable
        size_t num_of_calls_;       // This value stores how many times element was in the flow before
        size_t entered_iter_num;    // This value stores how many times element was in the flow before
};

/*==========================================================================================================================================*/

class LFU_cache
{  
    public:
        LFU_cache(const size_t& cache_size);
        ~LFU_cache();

        /**
         * Here must be 3 more from rule of 5
         * Copy constructor 
         * Copy assignment
         * Move assignment
        */

        void print_LFU_cache() const;           // prints all data about LFU_cache
        void print_page_list() const;  

        bool get_full_status() const;           // get the value of cache_is_full_
        void set_full_status(const bool& val);  // get the value of cache_is_full_
        size_t get_cache_size() const;          // gets tha value of cache_size_

    private:
        size_t cache_size_;   // stores the cache size
        bool cache_is_full_;  // stores the cache flag of being full
        Page_list page_list_; // 


        /** NOTE
         * 
         *here must be two containers 
         * 
        */
};  

/*==========================================================================================================================================*/

class Page_list
{
    friend LFU_cache;

    Page_list(const size_t& sequence_size);
    Page_list();
    ~Page_list();
    
    void print_page_list() const; // prints all elements of the list

   
    private:
        list sequence_;        // std::list typedef for list of pages
        size_t sequence_size_; // the number of elements in the std::list
};

/*==========================================================================================================================================*/

#endif
