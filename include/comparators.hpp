#ifndef COMPARATORS_HPP_TIM_A_D
#define COMPARATORS_HPP_TIM_A_D

#include "LFU.hpp"

int comparator_cache_val(const void* a_val, const void* b_val) //ok
{
	if (((const Cache_elem*)a_val)->elem_value_ > ((const Cache_elem*)b_val)->elem_value_)
    {
        return 1;
    }
	else if (((const Cache_elem*)a_val)->elem_value_ < ((const Cache_elem*)b_val)->elem_value_)
    {
        return -1;
    }

	return 0;
}

int comparator_cache_val_ptr(const void* a_val, const void* b_val) 
{
	if ((*((const Cache_elem**)a_val))->elem_value_ > (*((const Cache_elem**)b_val))->elem_value_)
    {
        return 1;
    }
	else if ((*((const Cache_elem**)a_val))->elem_value_ < (*((const Cache_elem**)b_val))->elem_value_)
    {
        return -1;
    }

	return 0;
}

int comparator_cache_freq(const void* a_val, const void* b_val) //ok
{
	if (((const Cache_elem*)a_val)->num_of_calls_ > ((const Cache_elem*)b_val)->num_of_calls_)
    {
        return 1;
    }
	else if (((const Cache_elem*)a_val)->num_of_calls_ < ((const Cache_elem*)b_val)->num_of_calls_)
    {
        return -1;
    }

	return 0;
}

int comparator_cache_freq_ptr(const void* a_val, const void* b_val) 
{
	if ((*((const Cache_elem**)a_val))->num_of_calls_ > (*((const Cache_elem**)b_val))->num_of_calls_)
    {
        return 1;
    }
	else if ((*((const Cache_elem**)a_val))->num_of_calls_ < (*((const Cache_elem**)b_val))->num_of_calls_)
    {
        return -1;
    }

	return 0;
}

int comparator_bsearch_val(const void* a_val, const void* b_val) // ok
{
    elem_type a_elem = ((Cache_elem*)a_val)->elem_value_;
    elem_type b_elem = ((Cache_elem*)b_val)->elem_value_;

    if (a_elem < b_elem)
    {
        return -1;
    }
    else if (a_elem > b_elem)
    {
        return 1;
    }
    
    return 0;
}

int comparator_bsearch_val_ptr(const void* a_val, const void* b_val) // ok
{
    elem_type a_elem = (*((Cache_elem**)a_val))->elem_value_;
    elem_type b_elem = (*((Cache_elem**)b_val))->elem_value_;

    if (a_elem < b_elem)
    {
        return -1;
    }
    else if (a_elem > b_elem)
    {
        return 1;
    }
    
    return 0;
}

int comparator_bsearch_freq(const void* a_val, const void* b_val) // ok
{
    elem_type a_elem = ((Cache_elem*)a_val)->num_of_calls_;
    elem_type b_elem = ((Cache_elem*)b_val)->num_of_calls_;

    if (a_elem < b_elem)
    {
        return -1;
    }
    else if (a_elem > b_elem)
    {
        return 1;
    }
        
    return 0;
}

#endif
