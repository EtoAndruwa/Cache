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

    auto start = std::chrono::high_resolution_clock::now();
    
    get_cache(cache, page_list);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;


    cache.print_LFU();

    return 0;
}
