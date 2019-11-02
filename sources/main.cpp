
#include <iostream>
#include <fstream>

#include <any>
#include <ctime>

#include "../include/SharedPtr.h"

int main()
{
    int*b=new int{5};
    SharedPtr<int> ptr(b);

    return 0;
}