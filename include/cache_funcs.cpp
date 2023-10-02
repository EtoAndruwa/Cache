#include "LRU.hpp"
#include "cache_funcs.hpp"

LRU_cache& fill_cache()
{
    
}

int get_input(int& cache_size, int& page_list_size)
{
    std::cin >> cache_size;
    
    if(cache_size <= 0)
    {
        return ERR_INV_CACHE_SIZE;
    }

    #ifdef DEBUG
        std::cout << "cache_size = " << cache_size << std::endl;
    #endif 

    std::cin >> page_list_size;
    
    if(page_list_size <= 0)
    {
        return ERR_INV_PAGE_L_SIZE;
    }

    #ifdef DEBUG
        std::cout << "page_list_size = " << page_list_size << std::endl;
    #endif

    return RETURN_OK;
}

// void print_page_list(list& list_ref)
// {
//     for (auto const &i: list_ref) {
//         std::cout << i << std::endl;
//     }
// }
