#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <fstream>
#include <climits>
#include <cstring>
class DataTable
{
public:
    DataTable(uint _max_file_num=1000,uint _max_file_data_rows=1000,uint _data_rows=0);
    ~DataTable();
    typedef int64_t KeyType;
    std::string get_data_status_info_name() const;
    uint get_max_rows() const;
    uint get_max_file_num() const;
    uint get_max_file_data_rows() const;
    uint get_data_rows() const;
    uint get_data_file_num() const;
    static DataTable* get_instance();
    static void instance_mutex_init();
    
    void search(int col=0,int minimum=LONG_MIN,int maximum=LONG_MAX);
    void insert(std::vector<KeyType>& keys);

private:
    static void lock(pthread_mutex_t* mutex);
    static void unlock(pthread_mutex_t* mutex);   
    
    static const std::string data_path;

    const uint max_rows=1000000;   //最大数据量
    const uint max_file_num;  //最大文件数
    const uint max_file_data_rows;   //每个文件最大数据量
    const static uint max_recent_file=5;
    uint data_rows;   //目前的数据行
    uint data_file_num;//目前已经存在的文件数目
    static DataTable* data_instance;         //Table对象实例
    std::vector<int> all_file;    //存储所有文件,以序号标识
    std::vector<pthread_mutex_t> all_file_mutex;  //所有文件的的互斥锁
    pthread_mutex_t all_file_usage_mutex;   //互斥访问
    std::vector<int> all_file_usage_status;   //所有文件使用状态

    std::map<int,std::fstream&> recent_file;   //最近的打开文件表
    pthread_mutex_t recent_file_mutex[max_recent_file];//对打开文件的锁
    
    //访问打开文件状态的锁
    static pthread_mutex_t recent_file_status_mutex;
    std::vector<int> recent_file_status;

    //整个表的所有文件信息
    static const  std::string data_status_info_name;;
    std::fstream data_status_info;
    pthread_mutex_t row_status_info_mutex;
    std::vector<int> file_row_info;

    //对象锁
    static pthread_mutex_t instance_mutex;     
    static pthread_mutex_t data_rows_mutex;
};

