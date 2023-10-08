#include "cache_funcs.hpp"
#include "comparators.hpp"

int get_page_list(Page_list& page_list, const int& page_list_size, std::fstream& file_ref) // ok
{
    elem_type temp = 0;
    page_list.page_list_size_ = page_list_size;

    for (size_t i = 0; i < page_list_size; i++)
    {   
        file_ref >> temp;
        page_list.page_list_ptr_.push_back(temp);
    }

    return RETURN_OK;
}

int get_input(int& cache_size, int& page_list_size, std::fstream& file_ref) // ok
{
    file_ref >> cache_size;
    if (cache_size <= 0)
    {
        return ERR_INV_CACHE_SIZE;
    }

    file_ref >> page_list_size;
    if (page_list_size <= 0)
    {
        return ERR_INV_PAGE_L_SIZE;
    }

    return RETURN_OK;
}

int get_cache(LFU_cache& LFU_cache_ref, Page_list& page_list) 
{
    list::iterator iter_list = page_list.page_list_ptr_.begin(); // iter_list to the start of page list
    const size_t cache_size = LFU_cache_ref.get_cache_size();
    Cache_elem** cache_ptr = LFU_cache_ref.get_ptr_to_arr();

    size_t iter_num = 1;
    size_t used_cache = 0;
    Cache_elem** found_cache_elem = nullptr;
    Cache_elem constyl_elem[1] = {0,0,0};
    size_t hits = 0;
    Cache_elem** twin_freq_cache_elem = nullptr;
    Cache_elem** result_cache_ptr = nullptr;


    Cache_elem** free_cache_ptr = cache_ptr + (cache_size - 1);
    Cache_elem** end_cache_ptr = cache_ptr + cache_size;

    const size_t size_of_cache_ptr = sizeof(Cache_elem*);
    size_t cache_block_num = 0;

    while (iter_num != page_list.page_list_size_ + 1)
    {
        cache_block_num = (end_cache_ptr - free_cache_ptr) - 1;
        
        #ifdef DEBUG
            std::cout << "\n++++++++++++++++++BEFORE qsort_val++++++++++++++++++\n";
            LFU_cache_ref.print_LFU();
            std::cout << "++++++++++++++++++BEFORE qsort_val++++++++++++++++++\n";
        #endif

        qsort(free_cache_ptr + 1, cache_block_num, size_of_cache_ptr, comparator_cache_val_ptr);
        
        #ifdef DEBUG
            std::cout << "\n++++++++++++++++++AFTER qsort_val++++++++++++++++++\n";
            LFU_cache_ref.print_LFU();
            std::cout << "++++++++++++++++++AFTER qsort_val++++++++++++++++++\n";
        #endif

        constyl_elem[0].elem_value_ = *iter_list; // costyl
        Cache_elem* constyl_elem_ptr = &(constyl_elem[0]);
        Cache_elem** constyl_elem_doub_ptr = &constyl_elem_ptr;

        found_cache_elem = (Cache_elem**)bsearch((const void*)(constyl_elem_doub_ptr), free_cache_ptr + 1, cache_block_num, size_of_cache_ptr, comparator_bsearch_val_ptr);
        
        if (found_cache_elem != nullptr)
        {
            (*found_cache_elem)->elem_value_   = *iter_list;
            (*found_cache_elem)->num_of_calls_ += 1;
            hits++;

            #ifdef DEBUG
                std::cout << "\n==========AFTER found elem==========\n";
                LFU_cache_ref.print_LFU();
                std::cout << "==========AFTER found elem==========\n";
            #endif

            iter_list++; // from left to right in the page list
            iter_num++;
            continue;
        }

        if (used_cache != cache_size) 
        {
            used_cache++;
            (*free_cache_ptr)->elem_value_   = *iter_list;
            (*free_cache_ptr)->num_of_calls_ = 1;
            (*free_cache_ptr)->num_of_iter_  = iter_num;

            #ifdef DEBUG
                std::cout << "\n==========AFTER adding new elem==========\n";
                std::cout << "*iter_list = " << *iter_list << std::endl;
                LFU_cache_ref.print_LFU();
                std::cout << "==========AFTER adding new elem==========\n";
            #endif

            free_cache_ptr--;
        }
        else
        {
            #ifdef DEBUG
                std::cout << "\n++++++++++++++++++BEFORE qsort_freq++++++++++++++++++\n";
                LFU_cache_ref.print_LFU();
                std::cout << "++++++++++++++++++BEFORE qsort_freq++++++++++++++++++\n";
            #endif

            qsort(cache_ptr, cache_size, size_of_cache_ptr, comparator_cache_freq_ptr); // now sorted by frequency

            #ifdef DEBUG
                std::cout << "\n++++++++++++++++++AFTER qsort_freq++++++++++++++++++\n";
                LFU_cache_ref.print_LFU();
                std::cout << "++++++++++++++++++AFTER qsort_freq++++++++++++++++++\n";
            #endif

            twin_freq_cache_elem = cache_ptr + 1;

            if ((*twin_freq_cache_elem)->num_of_calls_ != (*cache_ptr)->num_of_calls_ || twin_freq_cache_elem == end_cache_ptr)
            {
                result_cache_ptr = cache_ptr;
            }
            else
            {
                result_cache_ptr = twin_freq_cache_elem;

                if ((*twin_freq_cache_elem)->num_of_iter_ > (*cache_ptr)->num_of_iter_)
                {
                    result_cache_ptr = cache_ptr;
                }
            }

            (*result_cache_ptr)->elem_value_   = *iter_list;
            (*result_cache_ptr)->num_of_calls_ = 1;
            (*result_cache_ptr)->num_of_iter_  = iter_num;

            #ifdef DEBUG
                std::cout << "\n==========AFTER FIFO new elem==========\n";
                LFU_cache_ref.print_LFU();
                std::cout << "==========AFTER FIFO new elem==========\n";
            #endif
        }

        iter_list++; // from left to right in the page list
        iter_num++;
    }

    return hits;
}

int get_cache_old(LFU_cache& LFU_cache_ref, Page_list& page_list) 
{
    list::iterator iter_list = page_list.page_list_ptr_.begin(); // iter_list to the start of page list
    const size_t cache_size = LFU_cache_ref.get_cache_size();
    Cache_elem* cache_ptr = LFU_cache_ref.get_cache_ptr();

    size_t iter_num = 1;
    size_t used_cache = 0;
    Cache_elem* found_cache_elem = nullptr;
    Cache_elem constyl_elem[1] = {0,0,0};
    size_t hits = 0;
    Cache_elem* twin_freq_cache_elem = nullptr;
    Cache_elem* result_cache_ptr = nullptr;


    Cache_elem* free_cache_ptr = cache_ptr + cache_size - 1;
    const Cache_elem* end_cache_ptr = cache_ptr + cache_size;

    // std::cout << "N of blocks " <<   (end_cache_ptr - free_cache_ptr) << std::endl;

    // #ifdef DEBUG
    //     std::cout << "\n\n######### BEFORE ALL #########\n";
    //     LFU_cache_ref.print_LFU();
    //     std::cout << "######### BEFORE ALL #########\n";
    // #endif

    const size_t sizeof_cache_elem = sizeof(Cache_elem);
    size_t cache_block_num = 0;

    auto start = std::chrono::high_resolution_clock::now();

    while (iter_num != page_list.page_list_size_ + 1)
    {
        cache_block_num = (end_cache_ptr - free_cache_ptr) - 1;

        qsort(free_cache_ptr + 1, cache_block_num, sizeof_cache_elem, comparator_cache_val);

        constyl_elem[0].elem_value_ = *iter_list; // costyl
        found_cache_elem = (Cache_elem*)bsearch((const void*)(constyl_elem), free_cache_ptr + 1, cache_block_num, sizeof_cache_elem, comparator_bsearch_val);
        
        if(found_cache_elem != nullptr)
        {
            found_cache_elem->elem_value_   = *iter_list;
            found_cache_elem->num_of_calls_ += 1;
            hits++;

            iter_list++; // from left to right in the page list
            iter_num++;

            continue;
        }

        if(used_cache != cache_size) 
        {
            used_cache++;
            free_cache_ptr->elem_value_   = *iter_list;
            free_cache_ptr->num_of_calls_ = 1;
            free_cache_ptr->num_of_iter_  = iter_num;
            free_cache_ptr--;
        }
        else
        {
            qsort(cache_ptr, cache_size, sizeof_cache_elem, comparator_cache_freq); // now sorted by frequency

            twin_freq_cache_elem = cache_ptr + 1;

            if(twin_freq_cache_elem->num_of_calls_ != cache_ptr->num_of_calls_ || twin_freq_cache_elem == end_cache_ptr)
            {
                result_cache_ptr = cache_ptr;
            }
            else
            {
                result_cache_ptr = twin_freq_cache_elem;

                if(twin_freq_cache_elem->num_of_iter_ > cache_ptr->num_of_iter_)
                {
                    result_cache_ptr = cache_ptr;
                }
            }

            result_cache_ptr->elem_value_   = *iter_list;
            result_cache_ptr->num_of_calls_ = 1;
            result_cache_ptr->num_of_iter_  = iter_num;
        }

        iter_list++; // from left to right in the page list
        iter_num++;
    }

    return hits;
}

void clear_cache(LFU_cache& LFU_cache_ref) // ok
{
    Cache_elem* cache_ptr = LFU_cache_ref.get_cache_ptr();

    for (size_t i = 0; i < LFU_cache_ref.get_cache_size(); i++)
    {
        cache_ptr[i].elem_value_   = 0;
        cache_ptr[i].num_of_calls_ = 0;
        cache_ptr[i].num_of_iter_  = 0;
    }
}

int get_cache_on_map(LFU_cache& LFU_cache_ref, Page_list& page_list)
{
    std::unordered_map<int, Cache_elem> unord_map;

    list::iterator iter_list = page_list.page_list_ptr_.begin(); // iter_list to the start of page list
    const size_t cache_size = LFU_cache_ref.get_cache_size();
    const list::iterator list_end = page_list.page_list_ptr_.end(); // the end of the list


    Cache_elem cache_block;
    size_t iter_num = 1;
    size_t used_cache = 0;
    size_t hits = 0;

    while (iter_list != list_end)
    {
        auto search_iter = unord_map.find(*iter_list);


        if (search_iter != unord_map.end())    // found
        {
            search_iter->second.num_of_calls_++;    
            hits++;          
        }
        else // not found
        {
            if (used_cache != cache_size)
            {
                cache_block.elem_value_   = *iter_list;
                cache_block.num_of_calls_ = 1;
                cache_block.num_of_iter_  = iter_num;

                unord_map.insert(std::pair<int, Cache_elem>(*iter_list, cache_block));
                used_cache++;
            }
            else
            {
                std::unordered_map<int, Cache_elem>::iterator iter_search   = unord_map.begin();
                std::unordered_map<int, Cache_elem>::iterator iter_end      = unord_map.end();
                std::unordered_map<int, Cache_elem>::iterator first_found   = iter_search;
                std::unordered_map<int, Cache_elem>::iterator second_found  = iter_search; 
                elem_type min_call_value = (*iter_search).second.num_of_calls_;

                while (iter_search != iter_end) 
                {
                    if (min_call_value > (*iter_search).second.num_of_calls_)
                    {
                        first_found = iter_search;
                        min_call_value = (*iter_search).second.num_of_calls_;
                        iter_search++;
                        continue;
                    }

                    if (min_call_value == (*iter_search).second.num_of_calls_)
                    {
                        second_found = iter_search;
                    }

                    iter_search++;
                }

                if (first_found == second_found)
                {
                    unord_map.erase((*first_found).second.elem_value_);
                }
                else
                {
                    if ((*first_found).second.num_of_iter_ > (*second_found).second.num_of_iter_)
                    {
                       unord_map.erase((*second_found).second.elem_value_);
                    }
                    else
                    {
                        unord_map.erase((*first_found).second.elem_value_);
                    }
                }

                cache_block.elem_value_   = *iter_list;
                cache_block.num_of_calls_ = 1;
                cache_block.num_of_iter_  = iter_num;

                unord_map.insert(std::pair<int, Cache_elem>(*iter_list, cache_block));

                #ifdef DEBUG
                    std::cout << "min_call_value " << min_call_value << std::endl;
                    std::cout << "first_found = " << (*first_found).first << " " << (*first_found).second.num_of_calls_ << " " << (*first_found).second.num_of_iter_ << std::endl;
                    std::cout << "second_found = " << (*second_found).first << " " << (*second_found).second.num_of_calls_ << " " << (*second_found).second.num_of_iter_ << std::endl;
                #endif 
            }
        }

        iter_list++; // from left to right in the page list
        iter_num++;
    }

    // print_map(unord_map);
    return hits;
}


template<typename K, typename V>
void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) 
    {
        std::cout << "{'" << pair.first << "': " << pair.second.elem_value_ << " " << pair.second.num_of_calls_ << " " << pair.second.num_of_iter_ << "}\n";
    }
}

// void find_min_freq()
// {
//     for (auto& it: B) 
//     {
//     // Do stuff
//     cout << it.first;
//     }
// }

