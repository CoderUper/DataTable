#pragma once
#include "struct.h"
#include <iostream>
#include <cstring>
class BTree
{
public:
    BTree(Node* _root=NULL,int _num=0,Node* hot=NULL);
    ~BTree();
    void store_BPlusTree(std::fstream& indexfile);
    void bfs_print();
    int get_num();
    bool insert(keyType key);
    Node* search(keyType key);
private:
    
    Node* create_node();
    
    bool remove(keyType key);
    void SolveOverflow(Node* node);
    void SolveUnderflow(Node* node);
    void release(Node * root); 
    Node* root;
    Node* get_root() ;
    void update_level(Node* node);    int num;
    Node* hot;     //指向当前节点
};

