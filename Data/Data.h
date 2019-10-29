#pragma once
#include <vector>
#include <string>
#include <iostream>

class Data
{
public:
    Data() {}
    ~Data() {}
    typedef int64_t KeyType;
    virtual std::vector<KeyType> read(std::iostream&,int row)=0; 
    virtual int search(std::iostream&,KeyType key,int col)=0;
    virtual int write(std::iostream&,std::vector<KeyType>)=0;
    Index* index;
};

