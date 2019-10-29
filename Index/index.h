#pragma once
#include <iostream>
#include <vector>

class index
{
public:
    index() {}
    ~index() {}
    typedef int64_t KeyType;
    virtual void create_index(std::vector<KeyType>,int col)=0;
    virtual void read_index(int col)=0;
private:

};

