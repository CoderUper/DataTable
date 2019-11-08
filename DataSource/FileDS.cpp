#include "FileDS.h"
#include <cstdlib>
#include <ctime>
FileDS::FileDS()
{
}

FileDS::~FileDS()
{
}

//从文件中读数据
std::vector<KeyType>& FileDS::read()
{
    srand((int)time(0));
    for(int i=0;i<100;i++)
    {
        data.push_back(rand()%100000);
    }
    return data;
}

