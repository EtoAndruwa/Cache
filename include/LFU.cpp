#include "LFU.hpp"
 
void print_page_list(const list& page_list) // OK
{
    std::cout << "page_list: ";
    for (auto const &i: page_list) 
    {   
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

LFU_cache::LFU_cache(const int& cache_size)
{
    cache_size_     = cache_size;
    cache_is_full_  = false;
    cache_is_empt_  = true;

    cache_ptr_ = new Cache_elem[cache_size_];
    if (cache_ptr_ == nullptr)
    {
        std::cout << "LFU cache_ptr_ is nullptr" << std::endl;
    }
}

void LFU_cache::print_LFU() const // ok
{   
    #ifdef DEBUG
        std::cout << "\nLFU cache_size_: " << cache_size_ << std::endl;
        std::cout << "LFU page_list_size_: " << page_list_size_ << std::endl;
        std::cout << "LFU page_list_ ";
        print_page_list(page_list_);
    #endif
   
    std::cout << "==========Cache data==========\n";
    for (size_t i = 0; i < cache_size_; i++)
    {
        std::cout << "cache_ptr_[" << i << "]: " << cache_ptr_[i].elem_value_ << " " << cache_ptr_[i].num_of_calls_ << " " << cache_ptr_[i].num_of_iters_ << std::endl;
    }   
    std::cout << "==========Cache data==========\n\n";
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

bool LFU_cache::get_empty_status() const // ok
{
    return cache_is_empt_;
}

size_t LFU_cache::get_cache_size() const // ok
{
    return cache_size_;
}