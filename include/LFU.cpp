#include "LFU.hpp"
 
void print_page_list(const Page_list& page_list) // ok
{
    std::cout << "page_list: ";
    for (auto const &i: page_list.page_list_ptr_) 
    {   
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

LFU_cache::LFU_cache(const int& cache_size)
{
    cache_size_     = cache_size;
    cache_is_full_  = false;

    cache_ptr_ = new Cache_elem[cache_size_];
    if (cache_ptr_ == nullptr)
    {
        std::cout << "LFU cache_ptr_ is nullptr" << std::endl;
    }

    array_of_ptrs_ = new Cache_elem*[cache_size_];
    if (array_of_ptrs_ == nullptr)
    {
        std::cout << "LFU array_of_ptrs_ is nullptr" << std::endl;
    }

    for (size_t i = 0; i < cache_size; i++)
    {
        array_of_ptrs_[i] = &(cache_ptr_[i]);
    }

}

void LFU_cache::print_LFU() const // ok
{   
    #ifdef DEBUG
        std::cout << "\nLFU cache_size_: " << cache_size_ << std::endl;
    #endif
   
    std::cout << "==========Cache data==========\n";
    for (size_t i = 0; i < cache_size_; i++)
    {
        std::cout << "(" << &(cache_ptr_[i]) << ")cache_ptr_[" << i << "]: elem_value_ = " << cache_ptr_[i].elem_value_ << " num_of_calls_ = " << cache_ptr_[i].num_of_calls_ << " num_of_iter_ = " << cache_ptr_[i].num_of_iter_ << std::endl;
    }   
    std::cout << "==========Cache data==========\n\n";

    std::cout << "==========Pointers array==========\n";
    for (size_t i = 0; i < cache_size_; i++)
    {
        std::cout << "cache_ptr_[" << i << "] = " << array_of_ptrs_[i] << std::endl;
    }   
    std::cout << "==========Pointers array==========\n\n";

}

LFU_cache::~LFU_cache() // ok
{
    #ifdef DEBUG
        std::cout << "~LFU_cache()" << std::endl;
    #endif

    delete [] cache_ptr_;
}

bool LFU_cache::get_full_status() const // ok
{
    return cache_is_full_;
}

size_t LFU_cache::get_cache_size() const // ok
{
    return cache_size_;
}

Cache_elem* LFU_cache::get_cache_ptr() const
{
    return cache_ptr_;
}

void LFU_cache::set_full_status(const bool& val)
{
    cache_is_full_ = val;
}

Cache_elem** LFU_cache::get_ptr_to_arr() const
{
    return array_of_ptrs_;
}
