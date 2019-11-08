#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
typedef int64_t KeyType;
class DataSource
{
public:
    DataSource() {}
    ~DataSource() {}
    virtual std::vector<KeyType>& read()=0;
    std::vector<KeyType> data;
};

