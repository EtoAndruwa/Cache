#include "LFU.hpp"
#include "cache_funcs.hpp"

int get_page_list(list& page_list, const int& page_list_size)
{
    #ifdef DEBUG
        std::cout << "page_list_size = " << page_list_size << std::endl;
    #endif  

    elem_type temp = 0;

    for (size_t i = 0; i < page_list_size; i++)
    {   
        std::cin >> temp;
        page_list.push_back(temp);
    }

    return RETURN_OK;
}

int get_input(int& cache_size, int& page_list_size) // OK
{
    std::cin >> cache_size;
    
    if (cache_size <= 0)
    {
        return ERR_INV_CACHE_SIZE;
    }

    #ifdef DEBUG
        std::cout << "cache_size = " << cache_size << std::endl;
    #endif 

    std::cin >> page_list_size;
    
    if (page_list_size <= 0)
    {
        return ERR_INV_PAGE_L_SIZE;
    }

    #ifdef DEBUG
        std::cout << "page_list_size = " << page_list_size << std::endl;
    #endif

    return RETURN_OK;
}

int get_cache(LFU_cache& LFU_cache_ref)
{
    for (list::iterator iter = LFU_cache_ref.page_list_.begin(); iter != LFU_cache_ref.page_list_.end(); iter++)
    {
        if (!LFU_cache_ref.cache_is_full_)
        {
            for (size_t i = 0; i < LFU_cache_ref.cache_size_; i++)
            {
                bubble_sort(LFU_cache_ref.cache_ptr_, LFU_cache_ref.cache_size_);   

                if (LFU_cache_ref.cache_ptr_[i].num_of_calls_ == 0)
                {
                    LFU_cache_ref.cache_ptr_[i].elem_value_   = *iter;
                    LFU_cache_ref.cache_ptr_[i].num_of_calls_ += 1;
                }
                iter++;
            }

            LFU_cache_ref.cache_is_full_ = true;
        }
    }
}

// int is_hit()
// {


// }

int bubble_sort(Cache_elem* cache_ptr, const size_t& cache_size)
{
    int i = 0;
    int j = 0;
    bool swapped = false;
    for (i = 0; i < cache_size - 1; i++) 
    {
        for (j = 0; j < cache_size - i - 1; j++) 
        {
            if (cache_ptr[j].elem_value_ > cache_ptr[j + 1].elem_value_) 
            {
                std::swap(cache_ptr[j], cache_ptr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }

    #ifdef DEBUG
        std::cout << "\n==========Cache data==========\n";
        for (size_t i = 0; i < cache_size; i++)
        {
            std::cout << "cache_ptr_[" << i << "]: " << cache_ptr[i].elem_value_ << " " << cache_ptr[i].num_of_calls_ << std::endl;
        }   
        std::cout << "==========Cache data==========\n";
    #endif

    return RETURN_OK;
}

int binary_search(Cache_elem* cache_ptr, const size_t& cache_size, const elem_type& value)
{
    size_t middle = cache_size / 2;
    size_t start  = 0;
    size_t end    = cache_size - 1;

    #ifdef DEBUG
        std::cout << "start : " << start << std::endl;
        std::cout << "middle : " << middle << std::endl;
        std::cout << "end : " << end << std::endl;
    #endif 
    
    while (start != end)
    {
        if (cache_ptr[middle].elem_value_ ==  value)
        {
            return middle;
        }
        else if (value > cache_ptr[middle].elem_value_)
        {
            start = middle + 1;
            middle = (end + start) / 2;

            #ifdef DEBUG
                std::cout << "start : " << start << std::endl;
                std::cout << "middle : " << middle << std::endl;
                std::cout << "end : " << end << std::endl;
            #endif 
        }
        else
        {
            end = middle - 1;
            middle = (end + start) / 2;

            #ifdef DEBUG
                std::cout << "start : " << start << std::endl;
                std::cout << "middle : " << middle << std::endl;
                std::cout << "end : " << end << std::endl;
            #endif 
        }
    }

    return VALUE_WAS_NOT_FOUND;
}





