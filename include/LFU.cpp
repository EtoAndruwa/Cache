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

LFU_cache::LFU_cache(const int& cache_size, const int& page_list_size, const list& page_list)
{
    #ifdef DEBUG
        std::cout << "LFU_cache()" << std::endl;
    #endif

    cache_size_ = cache_size;
    page_list_size_ = page_list_size; 
    page_list_ = page_list;
    cache_is_full_ = false;
    cache_is_empt_ = true;

    cache_ptr_ = new Cache_elem[cache_size_];
    if (cache_ptr_ == nullptr)
    {
        std::cout << "LFU cache_ptr_ is nullptr" << std::endl;
    }
}

void LFU_cache::print_LFU()
{
    std::cout << "\nLFU cache_size_: " << cache_size_ << std::endl;
    std::cout << "LFU page_list_size_: " << page_list_size_ << std::endl;
    std::cout << "LFU page_list_ ";
    print_page_list(page_list_);
   
    std::cout << "\n==========Cache data==========\n";
    for (size_t i = 0; i < cache_size_; i++)
    {
        std::cout << "cache_ptr_[" << i << "]: " << cache_ptr_[i].elem_value_ << " " << cache_ptr_[i].num_of_calls_ << std::endl;
    }   
    std::cout << "==========Cache data==========\n";
}

LFU_cache::~LFU_cache()
{
    #ifdef DEBUG
        std::cout << "~LFU_cache()" << std::endl;
    #endif

    delete [] cache_ptr_;
}


