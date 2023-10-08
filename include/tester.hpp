#ifndef TESTER_HPP_TIM_A_D
#define TESTER_HPP_TIM_A_D

#include <string>
#include <chrono>
#include <fstream>

int test_cache(char* num_of_test_ptr);
void print_test_data(std::ofstream& file_ref, const int& num_of_hits, const double& time_taken, const char* const func_name);
void print_test_ending(std::ofstream& file_ref, const int& test_num);
void print_test_heading(std::ofstream& file_ref, const int& test_num);

#endif
