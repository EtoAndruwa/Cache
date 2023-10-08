#include "tester.hpp"
#include "cache_funcs.hpp"

int test_cache(char* num_of_test_ptr)
{
    int num_of_test = std::stoi(num_of_test_ptr, 0, 10); // converts the argv value to the int

    if(num_of_test > 0)
    {
        std::cout << num_of_test << "tests will be run\n";

        for(size_t test_num = 0; test_num <= num_of_test; test_num++)
        {
            int cache_size     = 0;     // the size of the cache
            int page_list_size = 0;     // the size of the page list with data
            int err_code = RETURN_OK;   // the error code

            std::string file_name = "../tests/data";
            std::string file_exten = ".txt";
            file_name = file_name + std::to_string(test_num);
            file_name = file_name + file_exten;


            std::cout << "Test " << test_num << " is running now...\n";
            // std::cout << "Data for test from " << file_name << std::endl;

            std::fstream test_file (file_name); // creates the file discr
            if (test_file.is_open()) 
            {
                if (err_code = get_input(cache_size, page_list_size, test_file))
                {
                    std::cout << "Error code: "  << err_code << std::endl;
                    return err_code;
                }

                Page_list page_list;
                if (err_code = get_page_list(page_list, page_list_size, test_file))
                {
                    std::cout << "Error code: "  << err_code << std::endl;
                    return err_code;
                }

                LFU_cache cache(cache_size);

                // here must be cache

                cache.print_LFU();
            }
            else
            {
                std::cout << "No such test file with name \'" << file_name << "\' in the ../tests folder\n";

                return ERR_NO_TEST_FILE; 
            }

            test_file.close(); // closes the file 
        }

        return RETURN_OK;
    }
    else
    {        
        std::cout << "No test ran\n";
        return RETURN_OK;
    }
}


void print_test_data()
{

}

