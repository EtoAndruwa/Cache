#include "LFU.hpp"
#include "cache_funcs.hpp"
#include "tester.hpp"

int main(int argc, char* argv[])
{   
    if(argc == 2)
    {
        int rtn_test_cache = test_cache(argv[1]);
        
        if(rtn_test_cache != RETURN_OK)
        {   
            std::cout << "ERROR occured during testing";
        }
        else
        {   
            std::cout << "All tests were okey!\n";
        }
    }

    // get_cache(cache, page_list);
    // clear_cache(cache);
    // get_cache_old(cache, page_list);

    // get_cache_on_map();



    // cache.print_LFU();

    return 0;
}
