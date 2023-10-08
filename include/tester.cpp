#include "tester.hpp"
#include "cache_funcs.hpp"

int test_cache(char* num_of_test_ptr)
{
    int num_of_test = std::stoi(num_of_test_ptr, 0, 10); // converts the argv value to the int

    std::string path_to_log   = "../logs/";
    std::string log_file_name = "test_log.txt";
    log_file_name = path_to_log + log_file_name;

    std::ofstream test_log_file (log_file_name);

    if (!test_log_file.is_open())
    {
        std::cout << "ERROR: The test's log file cannot be opened\n";
        return ERR_OPEN_TEST_LOG;
    }

    if(num_of_test > 0)
    {
        std::cout << num_of_test << "tests will be run\n";

        for(size_t test_num = 0; test_num <= num_of_test; test_num++)
        {
            int cache_size     = 0;     // the size of the cache
            int page_list_size = 0;     // the size of the page list with data
            int err_code       = RETURN_OK;   // the error code

            std::cout << "Test " << test_num << " is running now...\n";
            // std::cout << "Data for test from " << file_name << std::endl;

            // must be in the outer function
            std::string path_to_test_data = "../tests/";
            std::string data_file_name    = "data";
            std::string data_file_exten   = ".txt";
            data_file_name = path_to_test_data + data_file_name + std::to_string(test_num) + data_file_exten;

            std::fstream test_file (data_file_name); // creates the file discr
            if (! test_file.is_open()) 
            {
                std::cout << "No such test file with name \'" << data_file_name << "\' in the ../tests folder\n";
                return ERR_NO_TEST_FILE; 
            }

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

            int num_of_hits = 0;
            print_test_heading(test_log_file, test_num);


            // print_test_data(test_num, num_of_hits, );

            print_test_ending(test_log_file, test_num);

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


void print_test_data(std::ofstream& file_ref, const int& num_of_hits, const double& time_taken, const char* const func_name)
{   

}

void print_test_heading(std::ofstream& file_ref, const int& test_num)
{
    file_ref << "========== TEST " << test_num << " ==========\n";
}

void print_test_ending(std::ofstream& file_ref, const int& test_num)
{
    file_ref << "========== TEST " << test_num << " ==========\n";
}

