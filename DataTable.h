#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <climits>
#include <cstring>
class DataTable
{
public:
    DataTable(uint _max_file_num,uint _max_file_data_rows,uint _data_rows=0);
    ~DataTable();
    uint get_max_rows() const;
    uint get_max_file_num() const;
    uint get_max_file_data_rows() const;
    static DataTable* get_instance();
    static void instance_mutex_init();
    typedef int64_t KeyType;
    std::vector<int> search(KeyType key,int col=1,int minimum=LONG_MIN,int maximum=LONG_MAX);
    void insert(std::vector<KeyType> row);

private:
    static void lock(pthread_mutex_t* mutex);
    static void unlock(pthread_mutex_t* mutex);   
    
    const uint max_rows=1000000;   //最大数据量
    const uint max_file_num;  //最大文件数
    const uint max_file_data_rows;   //每个文件最大数据量
    const static uint max_recent_file=5;
    uint data_rows;   //目前的数据行
    static DataTable* data_instance;         //Table对象实例
    std::vector<int> all_file;    //存储所有文件,以序号标识

    std::map<int,std::fstream&> recent_file;   //最近的打开文件表
    static pthread_mutex_t recent_file_mutex;
    int recent_file_status[max_recent_file];

    static pthread_mutex_t instance_mutex;     //数据锁
    static pthread_mutex_t data_rows_mutex;
    std::vector<pthread_mutex_t> recent_mutex;
};

