#include "LFU.hpp"
#include "cache_funcs.hpp"

int get_page_list(list& page_list, const int& page_list_size)
{
    #ifdef DEBUG
        std::cout << "page_list_size = " << page_list_size << std::endl;
    #endif  

    elem_type temp = 0;

    for(size_t i = 0; i < page_list_size; i++)
    {   
        std::cin >> temp;
        page_list.push_back(temp);
    }

    return RETURN_OK;
}

int get_input(int& cache_size, int& page_list_size) // OK
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

