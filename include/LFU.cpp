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
}

void LFU_cache::print_LFU()
{
    std::cout << "LFU cache_size_: " << cache_size_ << std::endl;
    std::cout << "LFU page_list_size_: " << page_list_size_ << std::endl;
    std::cout << "LFU page_list_ ";
    print_page_list(page_list_);
}

LFU_cache::~LFU_cache()
{
    #ifdef DEBUG
        std::cout << "~LFU_cache()" << std::endl;
    #endif
}


