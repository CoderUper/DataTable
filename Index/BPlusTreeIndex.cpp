#include <iostream>
#include <cstdio>
#include "BPlusTreeIndex.h"

void BPlusTreeIndex::create_index(std::vector<KeyType> keys,int col)
{
    char col_c[64];
    sprintf(col_c,"%d.txt",col);
    std::string relative_path("../indexfile/");
    std::string index_file_path=relative_path+col_c;
    bt_file.open(index_file_path,std::ios::out);
   // std::vector<KeyType>::iterator it=keys.begin();
    auto it=keys.begin();
    auto it_end=keys.end();
    for(;it!=it_end;it++)
    {
        bt->insert(*it);
    }
    if(bt_file)
    {
        bt->store_BPlusTree(bt_file);

    }
    else
    {
        std::cout<<"建立索引失败，请重试\n";
    }
    if(bt_file.is_open())
        bt_file.close();
}

