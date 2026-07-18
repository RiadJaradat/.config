#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

class Infinity
{
public:
    bool negative = false;
};

bool operator>(Infinity a, int b)
{
    return true;
}

bool operator<(Infinity a, int b)
{
    return false;
}

Infinity inf;
cpp_int n = 10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000; 

int main()
{
    
}