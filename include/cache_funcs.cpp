#include "LFU.hpp"
#include "cache_funcs.hpp"

int get_page_list(Page_list& page_list, const int& page_list_size) // ok
{
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

    std::cin >> page_list_size;
    
    if (page_list_size <= 0)
    {
        return ERR_INV_PAGE_L_SIZE;
    }

    return RETURN_OK;
}

int get_cache(LFU_cache& LFU_cache_ref, Page_list& page_list) 
{
    list::iterator iter = page_list.page_list_ptr_.begin(); // iter to the start of page list
    size_t iter_num = 1;
    size_t used_cache = 0;
    Cache_elem* found_cache_elem = nullptr;
    Cache_elem constyl_elem[1] = {0,0,0};
    size_t hits = 0;

    while(iter != page_list.page_list_ptr_.end()) // till the end of page list
    {
        if (!LFU_cache_ref.get_full_status())
        {
            while (iter_num != page_list.page_list_size_ + 1)
            {
                if(iter != page_list.page_list_ptr_.begin()) // to reduce qsort call at start
                {
                    qsort(LFU_cache_ref.get_cache_ptr(), LFU_cache_ref.get_cache_size(), sizeof(Cache_elem), comparator_cache_val);
                }

                /** 
                 * Costyl below
                */
                constyl_elem[0].elem_value_ = *iter; // costyl
                found_cache_elem = (Cache_elem*)bsearch((const void*)(constyl_elem), LFU_cache_ref.get_cache_ptr(), LFU_cache_ref.get_cache_size(), sizeof(Cache_elem), comparator_bsearch_val);
                
                if(found_cache_elem == nullptr && used_cache < LFU_cache_ref.get_cache_size()) // tries to find existing page in the cache
                {
                    used_cache++;
                    (LFU_cache_ref.get_cache_ptr())[0].elem_value_   = *iter;
                    (LFU_cache_ref.get_cache_ptr())[0].num_of_calls_ = 1;
                    (LFU_cache_ref.get_cache_ptr())[0].num_of_iter_  = iter_num;

                    #ifdef DEBUG
                        std::cout << "\n\n######### New elem in cache AFTER #########\n";
                        LFU_cache_ref.print_LFU();
                        std::cout << "######### New elem in cache AFTER #########\n";
                    #endif
                }
                else if(found_cache_elem == nullptr && used_cache == LFU_cache_ref.get_cache_size())
                {
                    // std::cout << "\n\n######### comparator_cache_freq BEFORE #########\n";
                    // LFU_cache_ref.print_LFU();
                    // std::cout << "######### comparator_cache_freq BEFORE #########\n";

                    qsort(LFU_cache_ref.get_cache_ptr(), LFU_cache_ref.get_cache_size(), sizeof(Cache_elem), comparator_cache_freq); // know sorted for frequency
                   
                    size_t min_freq_val = LFU_cache_ref.get_cache_ptr()->num_of_calls_;
                    // std::cout << "min freq = " <<  min_freq_val << std::endl;
                    Cache_elem* min_freq_ptr = LFU_cache_ref.get_cache_ptr();

                    Cache_elem* twin_freq_cache_elem = (Cache_elem*)bsearch((const void*)(min_freq_ptr), (LFU_cache_ref.get_cache_ptr() + 1), LFU_cache_ref.get_cache_size(), sizeof(Cache_elem), comparator_bsearch_freq);
                    
                    if(twin_freq_cache_elem == nullptr)
                    {
                        // std::cout << "BEFORE: min_freq_ptr->elem_value = " << min_freq_ptr->elem_value_ << std::endl;
                        // std::cout << "BEFORE: min_freq_ptr->num_of_calls_ = " << min_freq_ptr->num_of_calls_ << std::endl;
                        // std::cout << "BEFORE: min_freq_ptr->num_of_iter_ = " << min_freq_ptr->num_of_iter_ << std::endl;

                        min_freq_ptr->elem_value_   = *iter;
                        min_freq_ptr->num_of_calls_ = 1;
                        min_freq_ptr->num_of_iter_  = iter_num;

                        // std::cout << "AFTER: min_freq_ptr->elem_value = " << min_freq_ptr->elem_value_ << std::endl;
                        // std::cout << "AFTER: min_freq_ptr->num_of_calls_ = " << min_freq_ptr->num_of_calls_ << std::endl;
                        // std::cout << "AFTER: min_freq_ptr->num_of_iter_ = " << min_freq_ptr->num_of_iter_ << std::endl;

                        // LFU_cache_ref.print_LFU();
                    }
                    else
                    {
                        if(twin_freq_cache_elem->num_of_iter_ > min_freq_ptr->num_of_iter_)
                        {
                            min_freq_ptr->elem_value_   = *iter;
                            min_freq_ptr->num_of_calls_ = 1;
                            min_freq_ptr->num_of_iter_  = iter_num;
                        }
                        else
                        {
                            twin_freq_cache_elem->elem_value_   = *iter;
                            twin_freq_cache_elem->num_of_calls_ = 1;
                            twin_freq_cache_elem->num_of_iter_  = iter_num;
                        }
                    }


                    // std::cout << "\n\n######### comparator_cache_freq AFTER #########\n";
                    // LFU_cache_ref.print_LFU();
                    // std::cout << "######### comparator_cache_freq AFTER #########\n";
                }
                else
                {
                    found_cache_elem->elem_value_   = *iter;
                    found_cache_elem->num_of_calls_ += 1;
                    hits++;

                    #ifdef DEBUG
                        std::cout << "\n\n######### Found in cache AFTER #########\n";
                        LFU_cache_ref.print_LFU();
                        std::cout << "######### Found in cache AFTER #########\n";
                    #endif
                }

                if(used_cache == LFU_cache_ref.get_cache_size()) // if all cache is used
                {   
                    LFU_cache_ref.set_full_status(true);
                }

                iter++; // from left to right in the page list
                iter_num++;
            }

            #ifdef DEBUG
                std::cout << "\n\n++++++Cache is full now++++++\n";
                LFU_cache_ref.print_LFU();
                std::cout << "+++++++++++++++++++++++++++++\n";
            #endif
        }

        iter++; // from left to right in the page list
    }

    // std::cout << "hits = " << hits << std::endl;
}

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

int comparator_cache_freq(const void* a_val, const void* b_val) //ok
{
	if (((const Cache_elem*)a_val)->num_of_calls_ > ((const Cache_elem*)b_val)->num_of_calls_)
    {
        return 1;
    }
	else if (((const Cache_elem*)a_val)->num_of_calls_ < ((const Cache_elem*)b_val)->num_of_calls_)
    {
        return -1;
    }

	return 0;
}

int comparator_bsearch_val(const void* a_val, const void* b_val) // ok
{
    elem_type a_elem = ((Cache_elem*)a_val)->elem_value_;
    elem_type b_elem = ((Cache_elem*)b_val)->elem_value_;

    if (a_elem < b_elem)
    {
        return -1;
    }
    else if (a_elem > b_elem)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int comparator_bsearch_freq(const void* a_val, const void* b_val) // ok
{
    elem_type a_elem = ((Cache_elem*)a_val)->num_of_calls_;
    elem_type b_elem = ((Cache_elem*)b_val)->num_of_calls_;

    if (a_elem < b_elem)
    {
        return -1;
    }
    else if (a_elem > b_elem)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
