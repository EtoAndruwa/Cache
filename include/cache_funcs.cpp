#include "LFU.hpp"
#include "cache_funcs.hpp"

int get_page_list(Page_list& page_list, const int& page_list_size) // ok
{
    #ifdef DEBUG
        std::cout << "page_list_size = " << page_list_size << std::endl;
    #endif  

    elem_type temp = 0;

    page_list.page_list_size_ = page_list_size;

    for (size_t i = 0; i < page_list_size; i++)
    {   
        std::cin >> temp;
        page_list.page_list_ptr_.push_back(temp);
    }

    return RETURN_OK;
}

int get_input(int& cache_size, int& page_list_size) // ok
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

int get_cache(LFU_cache& LFU_cache_ref, Page_list& page_list) 
{
    list::iterator iter = page_list.page_list_ptr_.begin(); // iter to the start of page list
    size_t iter_num = 1;
    size_t used_cache = 0;
    Cache_elem* found_cache_elem = nullptr;

    while(iter != page_list.page_list_ptr_.end()) // till the end of page list
    {
        if (!LFU_cache_ref.get_full_status())
        {
            while (iter_num == page_list.page_list_size_ || !LFU_cache_ref.get_full_status())
            {
                if(iter != page_list.page_list_ptr_.begin()) // to reduce qsort call at start
                {
                    #ifdef DEBUG
                        std::cout << "=======Before qsort(ITER "<< iter_num << ")=======\n";
                        LFU_cache_ref.print_LFU();
                        std::cout << "=======Before qsort(ITER "<< iter_num << ")=======\n";
                    #endif

                    qsort(LFU_cache_ref.get_cache_ptr(), LFU_cache_ref.get_cache_size(), sizeof(Cache_elem), comparator_cache_val);

                    #ifdef DEBUG
                        std::cout << "=======After qsort(ITER "<< iter_num << ")=======\n";
                        LFU_cache_ref.print_LFU();
                        std::cout << "=======After qsort(ITER "<< iter_num << ")=======\n";
                    #endif
                }

                found_cache_elem = (Cache_elem*)bsearch((const void*)(*iter), LFU_cache_ref.get_cache_ptr(), LFU_cache_ref.get_cache_size(), sizeof(Cache_elem), comparator_bsearch);
                
                if(found_cache_elem == nullptr && used_cache < LFU_cache_ref.get_cache_size()) // tries to find existing page in the cache
                {
                    #ifdef DEBUG
                        std::cout << "Not found in cache\n";
                    #endif

                    #ifdef DEBUG
                        std::cout << "######### New elem in cache BEFORE #########\n";
                        LFU_cache_ref.print_LFU();
                        std::cout << "######### New elem in cache BEFORE #########\n";
                    #endif

                    used_cache++;
                    (LFU_cache_ref.get_cache_ptr())[1].elem_value_   = *iter;
                    (LFU_cache_ref.get_cache_ptr())[1].num_of_calls_ = 1;
                    (LFU_cache_ref.get_cache_ptr())[1].num_of_iters_ = 1;

                    #ifdef DEBUG
                        std::cout << "######### New elem in cache AFTER #########\n";
                        LFU_cache_ref.print_LFU();
                        std::cout << "######### New elem in cache AFTER #########\n";
                    #endif
                }
                // else if(found_cache_elem == nullptr && used_cache == LFU_cache_ref.get_cache_size())
                // {

                // }
                else
                {
                    #ifdef DEBUG
                        std::cout << "Found in cache\n";
                        std::cout << "######### Found in cache BEFORE #########\n";
                        LFU_cache_ref.print_LFU();
                        std::cout << "######### Found in cache BEFORE #########\n";
                    #endif

                    found_cache_elem->elem_value_   = *iter;
                    found_cache_elem->num_of_calls_ += 1;
                    found_cache_elem->num_of_iters_ = iter_num;

                    #ifdef DEBUG
                        std::cout << "######### Found in cache AFTER #########\n";
                        LFU_cache_ref.print_LFU();
                        std::cout << "######### Found in cache AFTER #########\n";
                    #endif
                }

                if(used_cache == LFU_cache_ref.get_cache_size()) // if all cache is used
                {   
                    LFU_cache_ref.set_full_status(true);
                }

                // if (LFU_cache_ref.cache_ptr_[i].num_of_calls_ == 0)
                // {
                //     LFU_cache_ref.cache_ptr_[i].elem_value_   = *iter; // the value of current page in the page_list 
                //     LFU_cache_ref.cache_ptr_[i].num_of_calls_ += 1;    // the number of calls for this cache value in the page_list
                //     LFU_cache_ref.cache_ptr_[i].num_of_iters_ += 1;     // the number of iterations laying in the cache
                // }
                iter++; // from left to right in the page list
                iter_num++;
            }

            #ifdef DEBUG
                std::cout << "++++++Cache is full now++++++\n";
                LFU_cache_ref.print_LFU();
                std::cout << "+++++++++++++++++++++++++++++\n";
            #endif
        }
        // else
        // {



        // }

        iter++; // from left to right in the page list
    }
}

// int is_hit()
// {


// }


int comparator_cache_val(const void* a_val, const void* b_val) //ok
{
	if (((const Cache_elem*)a_val)->elem_value_ > ((const Cache_elem*)b_val)->elem_value_)
    {
        return 1;
    }
	else if (((const Cache_elem*)a_val)->elem_value_ < ((const Cache_elem*)b_val)->elem_value_)
    {
        return -1;
    }

	return 0;
}

int comparator_bsearch(const void* a_val, const void* b_val) // ok
{
    if (*((const int*)a_val) < *((const int*)b_val))
    {
        return -1;
    }
    else if (*((const int*)a_val) > *((const int*)b_val))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
