#include "my_module.hpp"

#define N_VALUES   32

int my_module(const int values)
{
    
    int sum = 0;
    
    for(int i = 0; i < N_VALUES; i += 1)
    {
        sum += values[ i ];
    }
    
    return sum;

};
