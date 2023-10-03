#include "LFU.hpp"
#include "cache_funcs.hpp"

#include <chrono>
using namespace std::chrono;

int main()
{   
    int cache_size     = 0;
    int page_list_size = 0;

    int err_code = RETURN_OK;

    if (err_code = get_input(cache_size, page_list_size))
    {
        std::cout << "Error code: "  << err_code << std::endl;
        return err_code;
    }

    Page_list page_list;
    if (err_code = get_page_list(page_list, page_list_size))
    {
        std::cout << "Error code: "  << err_code << std::endl;
        return err_code;
    }

    // print_page_list(page_list);

    LFU_cache cache(cache_size);

    clock_t start, end;
    start = clock();
    
    get_cache(cache, page_list);

    end = clock();

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed << time_taken << std::setprecision(5);
    std::cout << " sec " << std::endl;


    cache.print_LFU();

    return 0;
}
