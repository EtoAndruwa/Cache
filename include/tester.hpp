#ifndef TESTER_HPP_TIM_A_D
#define TESTER_HPP_TIM_A_D

#include "LFU.hpp"

#include <string>
#include <chrono>
#include <fstream>

#define MAX_FUNC_NAME_LENGTH 25

int test_cache(char* num_of_test_ptr);
void print_test_ending(std::ofstream& file_ref, const int& test_num);
void print_test_heading(std::ofstream& file_ref, const int& test_num);
void print_test_data(std::ofstream& file_ref, LFU_cache& LFU_cache_ref, Page_list& page_list, int (*func)(LFU_cache&, Page_list&), const char* const func_name);
#endif
