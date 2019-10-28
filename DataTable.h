#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
class DataTable
{
public:
    DataTable(uint _max_file_num,uint _max_file_data_rows,uint _data_rows);
    ~DataTable();
    uint get_max_rows() const;
    uint get_max_file_num() const;
    uint get_max_file_data_rows() const;
    static DataTable* get_instance();
    void instance_lock();
    void instance_unlock();
    typedef int64_t KeyType;
private:
    const uint max_rows=1000000;   //最大数据量
    const uint max_file_num;  //最大文件数
    const uint max_file_data_rows;   //每个文件最大数据量
    uint data_rows;   //目前的数据行
    static DataTable* data_instance;         //Table对象实例
    std::vector<int> all_file;    //存储所有文件,以序号标识
    std::map<int,std::fstream&> recent_file;   //最近的打开文件表
    pthread_mutex_t instance_mutex;     //数据锁
    std::vector< pthread_mutex_t> file_mutex;
    std::vector<pthread_mutex_t> recent_mutex;
};

