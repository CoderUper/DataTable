#pragma once
#include <iostream>
#include <vector>

class Index
{
public:
    Index() {}
    ~Index() {}
    typedef int64_t KeyType;
    virtual void create_index(std::vector<KeyType>,int col)=0;
private:
    
};

