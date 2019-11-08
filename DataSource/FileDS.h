#pragma once
#include "DataSource.h"
class FileDS:public DataSource
{
public:
    FileDS();
    ~FileDS();
    std::vector<KeyType>& read();
};

