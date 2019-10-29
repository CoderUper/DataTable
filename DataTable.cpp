#include "DataTable.h"

//instance_mutex初始化
pthread_mutex_t DataTable::instance_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DataTable::data_rows_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DataTable::recent_file_mutex=PTHREAD_MUTEX_INITIALIZER;

DataTable::DataTable(uint _max_file_num,uint _max_file_data_rows,uint _data_rows):max_file_num(_max_file_num),max_file_data_rows(_max_file_data_rows),data_rows(_data_rows)
{
    memset(recent_file_status,0,sizeof(recent_file_status));
}

uint DataTable::get_max_rows() const
{
    return max_rows;
}

uint DataTable::get_max_file_num() const
{
    return max_file_num;
}

uint DataTable::get_max_file_data_rows() const
{
    return max_file_data_rows;
}

void DataTable::lock(pthread_mutex_t* mutex)
{
    pthread_mutex_lock(mutex);
}

void DataTable::unlock(pthread_mutex_t* mutex)
{
    pthread_mutex_unlock(mutex);
}


//单例模式，获取对象实例
DataTable* DataTable::get_instance()
{
    if(data_instance==NULL)
    {
        lock(&instance_mutex);
        if(data_instance==NULL)
        {
            data_instance=new DataTable(1000,1000);
        }
        unlock(&instance_mutex);
    }
    return data_instance;
}

//查询数据
std::vector<int>  DataTable::search(KeyType key,int col,int minimum,int maximum)
{
    //查看是否为这列建立索引
    //如果有，用B+树搜索
    //没有的话
    //用B+树索引开始搜索
    //最近打开文件没有搜索到，搜索
}

//向某一列插入一行数据
void DataTable::insert(std::vector<KeyType> row)
{
    //先找最近打开文件
    lock(&recent_file_mutex);
    for(int i=0;i<max_recent_file;i++)
    {
        if(recent_file[i]&&)
    }
    //若没满，被占用则插入
    //若满了，或者被占用则插入磁盘中的文件
}
