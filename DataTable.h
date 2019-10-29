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
    typedef int64_t KeyType;
    std::string get_data_status_info_name() const;
    uint get_max_rows() const;
    uint get_max_file_num() const;
    uint get_max_file_data_rows() const;
    uint get_data_rows() const;
    uint get_data_file_num() const;
    std::vector<KeyType> split(const std::string& str,const std::string& delim);
    static DataTable* get_instance();
    static void instance_mutex_init();
    
    std::vector<int> search(KeyType key,int col=0,int minimum=LONG_MIN,int maximum=LONG_MAX);
    void insert(std::vector<KeyType> row);

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

    std::map<int,std::fstream&> recent_file;   //最近的打开文件表
    pthread_mutex_t recent_file_mutex[max_recent_file];//对打开文件的锁
    
    //访问打开文件状态的锁
    static pthread_mutex_t recent_file_status_mutex;
    int recent_file_status[max_recent_file];

    //整个表的所有文件信息
    static const  std::string data_status_info_name;;
    std::fstream data_status_info;
    static pthread_mutex_t data_status_info_mutex;

    //对象锁
    static pthread_mutex_t instance_mutex;     
    static pthread_mutex_t data_rows_mutex;
};

