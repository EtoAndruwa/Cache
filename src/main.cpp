#include "LRU.hpp"
#include "cache_funcs.hpp"

int main()
{   
    int cache_size     = 0;
    int page_list_size = 0;

    int err_code = RETURN_OK;

    if(err_code = get_input(cache_size, page_list_size))
    {
        std::cout << "Error code: "  << err_code << std::endl;
        return err_code;
    }

    list page_list;
    page_list.push_back(1);
    page_list.push_back(2);
    page_list.push_back(3);
    page_list.push_back(4);
    // print_page_list(page_list);

    for (auto const &i: page_list) {
        std::cout << i << " ";
    }
    

    return 0;
}
