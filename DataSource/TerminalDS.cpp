#include <iostream>
#include "TerminalDS.h"
#define int64_t KeyType
std::vector<KeyType>& TerminalDS::read()
{
    std::cout<<"请从控制台输入100个数据:";
    int n=0;
    while(n<100)
    {
        KeyType elem=0;
        std::cin>>elem;
        data.push_back(elem);
        n++;
    }
    return data;
}
