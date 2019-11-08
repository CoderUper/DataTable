#pragma once
#include "DataSource.h"

//数据来源于终端控制台控制台
class TerminalDS:public DataSource
{
public:
    TerminalDS() {}
    ~TerminalDS() {}
    std::vector<KeyType>& read();
};

