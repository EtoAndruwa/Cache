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
    size_t sort_falg = UNSORTED;

    while (iter_num != page_list.page_list_size_ + 1)
    {
        cache_block_num = (end_cache_ptr - free_cache_ptr) - 1;
        
        #ifdef DEBUG
            std::cout << "\n++++++++++++++++++BEFORE qsort_val++++++++++++++++++\n";
            LFU_cache_ref.print_LFU();
            std::cout << "++++++++++++++++++BEFORE qsort_val++++++++++++++++++\n";
        #endif

        if(sort_falg == UNSORTED)
        {
            qsort(free_cache_ptr + 1, cache_block_num, size_of_cache_ptr, comparator_cache_val_ptr);
            sort_falg = SORTED_BY_VAL;
        }
        
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
            std::cout << "\n+++++++++++Found in cache+++++++++++++\n";
            LFU_cache_ref.print_LFU();
            (*found_cache_elem)->num_of_calls_ += 1;

            std::cout << "Hit on elem: " << *iter_list << std::endl; 
            std::cout << "\nHits before: " << hits << std::endl;
            hits++;
            std::cout << "Hits after: " << hits << std::endl << std::endl;

            // std::cout << "\n==========AFTER found elem==========\n"
            // std::cout << "==========AFTER found elem==========\n";
            LFU_cache_ref.print_LFU();
            std::cout << "+++++++++++Found in cache+++++++++++++\n";

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

            std::cout << "\n+++++++++++Cache increased+++++++++++++\n";
            LFU_cache_ref.print_LFU();
            std::cout << "+++++++++++Cache increased+++++++++++++\n";


            sort_falg = UNSORTED;

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
            sort_falg = UNSORTED;

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

            std::cout << "\n+++++++++++Cache full+++++++++++++\n";
            LFU_cache_ref.print_LFU();
            std::cout << "+++++++++++Cache full+++++++++++++\n";

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
            found_cache_elem->num_of_calls_ += 1;
            hits++;

            // std::cout << "Hit on value = " << *iter_list << std::endl;
            // std::cout << "Hits now = " << hits << std::endl; 

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
    Cache_elem** arr_ptr  = LFU_cache_ref.get_ptr_to_arr();
    const auto cache_size = LFU_cache_ref.get_cache_size();

    for (size_t i = 0; i < cache_size; i++)
    {
        cache_ptr[i].elem_value_   = 0;
        cache_ptr[i].num_of_calls_ = 0;
        cache_ptr[i].num_of_iter_  = 0;

        arr_ptr[i] = &cache_ptr[i];
    }
}

int get_cache_on_map(LFU_cache& LFU_cache_ref, Page_list& page_list)
{
    std::unordered_map<int, Cache_elem> unord_map;

    list::iterator iter_list = page_list.page_list_ptr_.begin(); // iter_list to the start of page list
    const size_t cache_size = LFU_cache_ref.get_cache_size();
    const list::iterator list_end = page_list.page_list_ptr_.end(); // the end of the list  

    auto unord_map_iter = unord_map.begin();
    std::vector<Cache_elem> cache_vector;
    std::vector<Cache_elem>::iterator iter_vector = cache_vector.begin();

    Cache_elem cache_block;
    size_t iter_num = 1;
    size_t used_cache = 0;
    size_t hits = 0;
    // size_t sort_flag = UNSORTED;

    std::unordered_map<int, Cache_elem>::iterator search_iter;
    const auto unord_map_end = unord_map.end();

    while (iter_list != list_end)
    {
        search_iter = unord_map.find(*iter_list);

        if (search_iter != unord_map_end)    // found
        {
            std::cout << "\n===========Found in cache===========" << std::endl; 
            print_map(unord_map);
            std::cout << "Hit on elem: " << *iter_list << std::endl; 
            std::cout << "\nHits before: " << hits << std::endl;
            search_iter->second.num_of_calls_++; 
            hits++; 
            std::cout << "Hits after: " << hits << std::endl << std::endl;

            for(auto vec: cache_vector) 
            {
                std::cout << "[" << vec.elem_value_ << " " << vec.num_of_calls_ << " " << vec.num_of_iter_ << "]" << std::endl;
            }

            std::vector<Cache_elem>::iterator vector_search_iter = cache_vector.begin();
            while(vector_search_iter != cache_vector.end())
            {
                if((*vector_search_iter).elem_value_ == *iter_list)
                {
                    std::cout << "FOUND!\n";
                    (*vector_search_iter).num_of_calls_++;
                    break;
                }
                vector_search_iter++;
            }

            std::cout << std::endl;
    
            for(auto vec: cache_vector) 
            {
                std::cout << "[" << vec.elem_value_ << " " << vec.num_of_calls_ << " " << vec.num_of_iter_ << "]" << std::endl;
            }
            // here must be increase of the call num in the VECTOR!!!!!


            print_map(unord_map);
            std::cout << "===========Found in cache===========" << std::endl;
        }
        else // not found
        {
            if (used_cache == cache_size)
            {
                std::cout << "\n===========Cache full===========" << std::endl;
                std::sort(cache_vector.begin(), cache_vector.end(), custom_op);
                // sort_flag = SORTED_BY_FREQ;
                print_map(unord_map);

                for(auto vec: cache_vector) 
                {
                    std::cout << "[" << vec.elem_value_ << " " << vec.num_of_calls_ << " " << vec.num_of_iter_ << "]" << std::endl;
                }

                if((cache_vector[0].num_of_calls_ != cache_vector[1].num_of_calls_) || (cache_size == 1))
                {
                    std::cout << "case 0 " << std::endl;
                    unord_map.erase(cache_vector[0].elem_value_);
                    
                    cache_vector[0].elem_value_   = *iter_list;
                    cache_vector[0].num_of_calls_ = 1;
                    cache_vector[0].num_of_iter_  = iter_num;
                }
                else
                {
                    if(cache_vector[0].num_of_iter_ > cache_vector[1].num_of_iter_)
                    {
                        std::cout << "case 1 " << std::endl;

                        std::cout << "erasing " << cache_vector[1].elem_value_ << std::endl;
                        std::cout << "inserting " << *iter_list << std::endl;
                        unord_map.erase(cache_vector[1].elem_value_);
                        
                        cache_vector[1].elem_value_   = *iter_list;
                        cache_vector[1].num_of_calls_ = 1;
                        cache_vector[1].num_of_iter_  = iter_num;
                    }
                    else
                    {
                        std::cout << "case 2 " << std::endl;
                        std::cout << "erasing " << cache_vector[0].elem_value_ << std::endl;
                        std::cout << "inserting " << *iter_list << std::endl;
                        unord_map.erase(cache_vector[0].elem_value_);
                        
                        cache_vector[0].elem_value_   = *iter_list;
                        cache_vector[0].num_of_calls_ = 1;
                        cache_vector[0].num_of_iter_  = iter_num;
                    } 
                }

                cache_block.elem_value_   = *iter_list;
                cache_block.num_of_calls_ = 1;      
                cache_block.num_of_iter_  = iter_num;

                unord_map.insert(std::pair<int, Cache_elem>(*iter_list, cache_block));

                for(auto vec: cache_vector) 
                {
                    std::cout << "[" << vec.elem_value_ << " " << vec.num_of_calls_ << " " << vec.num_of_iter_ << "]" << std::endl;
                }

                print_map(unord_map);
                std::cout << "===========Cache full===========\n" << std::endl; 
            }
            else
            {
                std::cout << "case 3\n";

                cache_block.elem_value_   = *iter_list;
                cache_block.num_of_calls_ = 1;      
                cache_block.num_of_iter_  = iter_num;

                used_cache++;
                // sort_flag = UNSORTED;

                iter_vector = cache_vector.insert(iter_vector, cache_block); // adding new elem to the vector
                unord_map.insert(std::pair<int, Cache_elem>(*iter_list, cache_block));
                
                std::cout << "\n===========Cache increased===========" << std::endl;
                print_map(unord_map);
                std::cout << "===========Cache increased===========\n" << std::endl;
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

