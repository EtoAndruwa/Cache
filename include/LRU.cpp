#include "LRU.hpp"
 
Cache_elem::Cache_elem()
{
    #ifdef DEBUG
        std::cout << "CONSTRUCTOR Cache_elem\n" << std::endl;
    #endif


}

Cache_elem::~Cache_elem()
{
    #ifdef DEBUG
        std::cout << "DESTRUCTOR Cache_elem\n" << std::endl;
    #endif


}

LRU_cache::LRU_cache()
{
    #ifdef DEBUG
        std::cout << "CONSTRUCTOR LRU_cache\n" << std::endl;
    #endif


}

LRU_cache::~LRU_cache()
{
    #ifdef DEBUG
        std::cout << "DESTRUCTOR LRU_cache\n" << std::endl;
    #endif

    
}