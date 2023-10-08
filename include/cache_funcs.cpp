#include "cache_funcs.hpp"
#include "comparators.hpp"

int get_page_list(Page_list& page_list, const int& page_list_size, std::fstream& file_ref) 
{
    elem_type temp = 0;

    page_list.page_list_size_ = page_list_size;

    for (size_t i = 0; i < page_list_size; i++)
    {   
        file_ref >> temp;

        std::cout << "temp(" << i << ") = " << temp << std::endl;

        page_list.page_list_ptr_.push_back(temp);
    }

    return RETURN_OK;
}

int get_input(int& cache_size, int& page_list_size, std::fstream& file_ref) 
{
    file_ref >> cache_size;

    std::cout << "cache_size " << cache_size << std::endl;
    
    if (cache_size <= 0)
    {
        return ERR_INV_CACHE_SIZE;
    }

    file_ref >> page_list_size;

    std::cout << "page_list_size " << page_list_size << std::endl;
    
    if (page_list_size <= 0)
    {
        return ERR_INV_PAGE_L_SIZE;
    }

    return RETURN_OK;
}

int get_cache(LFU_cache& LFU_cache_ref, Page_list& page_list) 
{
    list::iterator iter = page_list.page_list_ptr_.begin(); // iter to the start of page list
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

    // std::cout << "N of blocks " <<   (end_cache_ptr - free_cache_ptr) << std::endl;

    // #ifdef DEBUG
    //     std::cout << "\n\n######### BEFORE ALL #########\n";
    //     LFU_cache_ref.print_LFU();
    //     std::cout << "######### BEFORE ALL #########\n";
    // #endif

    const size_t size_of_cache_ptr = sizeof(Cache_elem*);
    size_t cache_block_num = 0;

    auto start = std::chrono::high_resolution_clock::now();

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

        constyl_elem[0].elem_value_ = *iter; // costyl
        Cache_elem* constyl_elem_ptr = &(constyl_elem[0]);
        Cache_elem** constyl_elem_doub_ptr = &constyl_elem_ptr;

        found_cache_elem = (Cache_elem**)bsearch((const void*)(constyl_elem_doub_ptr), free_cache_ptr + 1, cache_block_num, size_of_cache_ptr, comparator_bsearch_val_ptr);
        
        if (found_cache_elem != nullptr)
        {
            (*found_cache_elem)->elem_value_   = *iter;
            (*found_cache_elem)->num_of_calls_ += 1;
            hits++;

            #ifdef DEBUG
                std::cout << "\n==========AFTER found elem==========\n";
                LFU_cache_ref.print_LFU();
                std::cout << "==========AFTER found elem==========\n";
            #endif

            iter++; // from left to right in the page list
            iter_num++;
            continue;
        }

        if (used_cache != cache_size) 
        {
            used_cache++;
            (*free_cache_ptr)->elem_value_   = *iter;
            (*free_cache_ptr)->num_of_calls_ = 1;
            (*free_cache_ptr)->num_of_iter_  = iter_num;

            #ifdef DEBUG
                std::cout << "\n==========AFTER adding new elem==========\n";
                std::cout << "*iter = " << *iter << std::endl;
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

            (*result_cache_ptr)->elem_value_   = *iter;
            (*result_cache_ptr)->num_of_calls_ = 1;
            (*result_cache_ptr)->num_of_iter_  = iter_num;

            #ifdef DEBUG
                std::cout << "\n==========AFTER FIFO new elem==========\n";
                LFU_cache_ref.print_LFU();
                std::cout << "==========AFTER FIFO new elem==========\n";
            #endif
        }

        iter++; // from left to right in the page list
        iter_num++;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "(NEW CACHE)Execution time: " << duration.count() << " seconds. Hits: "<< hits << std::endl;
}

int get_cache_old(LFU_cache& LFU_cache_ref, Page_list& page_list) 
{
    list::iterator iter = page_list.page_list_ptr_.begin(); // iter to the start of page list
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

        constyl_elem[0].elem_value_ = *iter; // costyl
        found_cache_elem = (Cache_elem*)bsearch((const void*)(constyl_elem), free_cache_ptr + 1, cache_block_num, sizeof_cache_elem, comparator_bsearch_val);
        
        if(found_cache_elem != nullptr)
        {
            found_cache_elem->elem_value_   = *iter;
            found_cache_elem->num_of_calls_ += 1;
            hits++;

            iter++; // from left to right in the page list
            iter_num++;

            continue;
        }

        if(used_cache != cache_size) 
        {
            used_cache++;
            free_cache_ptr->elem_value_   = *iter;
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

            result_cache_ptr->elem_value_   = *iter;
            result_cache_ptr->num_of_calls_ = 1;
            result_cache_ptr->num_of_iter_  = iter_num;
        }

        iter++; // from left to right in the page list
        iter_num++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "(OLD CACHE)Execution time: " << duration.count() << " seconds. Hits: "<< hits << std::endl;
}

void clear_cache(LFU_cache& LFU_cache_ref)
{
    Cache_elem* cache_ptr = LFU_cache_ref.get_cache_ptr();

    for (size_t i = 0; i < LFU_cache_ref.get_cache_size(); i++)
    {
        cache_ptr[i].elem_value_ = 0;
        cache_ptr[i].num_of_calls_ = 0;
        cache_ptr[i].num_of_iter_ = 0;
    }
}

// int get_cache_on_map(LFU_cache& LFU_cache_ref, Page_list& page_list)
// {
//     std::unordered_map<std::string, Cache_elem> map_ptr;

//     list::iterator iter = page_list.page_list_ptr_.begin(); // iter to the start of page list
//     const size_t cache_size = LFU_cache_ref.get_cache_size();

//     size_t iter_num = 1;
//     size_t used_cache = 0;
//     size_t hits = 0;

//     auto start = std::chrono::high_resolution_clock::now();

//     while (iter_num != page_list.page_list_size_ + 1)
//     {
//         constyl_elem[0].elem_value_ = *iter; // costyl
//         Cache_elem* constyl_elem_ptr = &(constyl_elem[0]);
//         Cache_elem** constyl_elem_doub_ptr = &constyl_elem_ptr;

//         found_cache_elem = (Cache_elem**)bsearch((const void*)(constyl_elem_doub_ptr), free_cache_ptr + 1, cache_block_num, size_of_cache_ptr, comparator_bsearch_val_ptr);
        
//         if (found_cache_elem != nullptr)
//         {
//             (*found_cache_elem)->elem_value_   = *iter;
//             (*found_cache_elem)->num_of_calls_ += 1;
//             hits++;

//             iter++; // from left to right in the page list
//             iter_num++;
//             continue;
//         }

//         if (used_cache != cache_size) 
//         {
//             used_cache++;
//             (*free_cache_ptr)->elem_value_   = *iter;
//             (*free_cache_ptr)->num_of_calls_ = 1;
//             (*free_cache_ptr)->num_of_iter_  = iter_num;

//             #ifdef DEBUG
//                 std::cout << "\n==========AFTER adding new elem==========\n";
//                 std::cout << "*iter = " << *iter << std::endl;
//                 LFU_cache_ref.print_LFU();
//                 std::cout << "==========AFTER adding new elem==========\n";
//             #endif

//             free_cache_ptr--;
//         }
//         else
//         {
//             qsort(cache_ptr, cache_size, size_of_cache_ptr, comparator_cache_freq_ptr); // now sorted by frequency

//             twin_freq_cache_elem = cache_ptr + 1;

//             if ((*twin_freq_cache_elem)->num_of_calls_ != (*cache_ptr)->num_of_calls_ || twin_freq_cache_elem == end_cache_ptr)
//             {
//                 result_cache_ptr = cache_ptr;
//             }
//             else
//             {
//                 result_cache_ptr = twin_freq_cache_elem;

//                 if ((*twin_freq_cache_elem)->num_of_iter_ > (*cache_ptr)->num_of_iter_)
//                 {
//                     result_cache_ptr = cache_ptr;
//                 }
//             }

//             (*result_cache_ptr)->elem_value_   = *iter;
//             (*result_cache_ptr)->num_of_calls_ = 1;
//             (*result_cache_ptr)->num_of_iter_  = iter_num;
//         }

//         iter++; // from left to right in the page list
//         iter_num++;
//     }



//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;
//     std::cout << "(NEW CACHE)Execution time: " << duration.count() << " seconds. Hits: "<< hits << std::endl;

//     print_map(map_ptr);
// }


template<typename K, typename V>
void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{'" << pair.first << "': " << pair.second.elem_value_ << pair.second.num_of_calls_ << pair.second.num_of_iter_ << "}\n";
    }
}
