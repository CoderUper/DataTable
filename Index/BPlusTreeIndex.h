#pragma once
#include "index.h"
#include "../BPlusTree/BTree.h"
#include <fstream>
class BPlusTreeIndex:public Index
{
public:
    BPlusTreeIndex():bt(NULL) {}
    ~BPlusTreeIndex() {  if(bt_file.is_open()) bt_file.close();  }
    void create_index(std::vector<KeyType>,int col);
private:
    BTree *bt;
    std::fstream bt_file;
};

