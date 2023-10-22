#include "LFU.hpp"
 
/*==========================================================================================================================================*/

void LFU_cache::print_page_list() const
{
    std::cout << "\n=====================================\n" << "page_list: ";
    for (auto const &page_list_elem: page_list_.sequence_) 
    {   
        std::cout << page_list_elem << " ";
    }
    std::cout << std::endl << "=====================================\n";
}

LFU_cache::LFU_cache(const size_t& cache_size)
{
    cache_size_    = cache_size;
    cache_is_full_ = false;
}

void LFU_cache::print_LFU_cache() const // ok
{   

}

LFU_cache::~LFU_cache()
{
    std::cout << "Destuctor for LFU_cache\n";
}

bool LFU_cache::get_full_status() const 
{
    return cache_is_full_;
}

size_t LFU_cache::get_cache_size() const 
{
    return cache_size_;
}

void LFU_cache::set_full_status(const bool& val)
{
    cache_is_full_ = val;
}

/*==========================================================================================================================================*/

Page_list::Page_list(const size_t& sequence_size) 
{
    std::cout << "Cast constuctor Page list\n";

    /*
        Is it okey to initialize list like this??
    */

    elem_type temp = 0;

    for (size_t i = 0; i < sequence_size; i++)
    {
        std::cin >> temp;
        sequence_.push_back(temp);
    }
}   

Page_list::~Page_list()
{
    std::cout << "Destructor Page list\n";
}

void Page_list::print_page_list() const
{   
    std::cout << "\n========LIST=========\n";

    for (const auto& list_elem: sequence_)
    {
        std::cout << list_elem << " ";
    }

    std::cout << "\n";
    std::cout << "========LIST=========\n";
}

Page_list::Page_list() 
{
    std::cout << "Default constuctor Page list\n";
}  

