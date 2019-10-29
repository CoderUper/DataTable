#include "DataTable.h"
#include <unistd.h>

//mutex初始化
pthread_mutex_t DataTable::instance_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DataTable::data_rows_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DataTable::recent_file_status_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DataTable::data_status_info_mutex=PTHREAD_MUTEX_INITIALIZER;
const std::string DataTable::data_status_info_name="data_status_info.txt";
const std::string DataTable::data_path="./data/";
DataTable::DataTable(uint _max_file_num,uint _max_file_data_rows,uint _data_rows):max_file_num(_max_file_num),max_file_data_rows(_max_file_data_rows),data_rows(_data_rows)
{
    memset(recent_file_status,0,sizeof(recent_file_status));
    for(int i=0;i<max_recent_file;i++)
    {
        pthread_mutex_init(&recent_file_mutex[i],NULL);
    }
    std::string file_path=data_path+get_data_status_info_name();
    if(access(file_path.c_str(),F_OK)==0)
    {
        data_status_info.open(file_path);
    }
    else
    {
        data_status_info.open(file_path);
        data_status_info<<0<<"\n";    //写入已经存在的文件数
        for(int i=0;i<max_file_num;i++)
        {
            data_status_info<<i<<" "<<0<<"\n";
        }
        data_rows=0;
        data_file_num=0;
    }   
}

uint DataTable::get_data_rows() const 
{
    return data_rows; 
}

uint DataTable::get_data_file_num() const
{
    return data_file_num;
}

std::string DataTable::get_data_status_info_name() const
{
    return data_status_info_name;
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

std::vector<DataTable::KeyType> split(const std::string& str, const std::string& delim) {  
        std::vector<DataTable::KeyType> res;  
        if("" == str) return res;  
        //先将要切割的字符串从string类型转换为char*类型  
        char * strs = new char[str.length() + 1] ; //不要忘了  
        strcpy(strs, str.c_str());   
                       
        char * d = new char[delim.length() + 1];  
        strcpy(d, delim.c_str());  
                               
        char *p = strtok(strs, d);  
        while(p) {  
            string s = p; //分割得到的字符串转换为string类型  
            res.push_back(s); //存入结果数组  
            p = strtok(NULL, d);  
        }  
                                                                   
        return res;  
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
        if(recent_file_status[i]&&)
    }
    //若没满，被占用则插入
    //若满了，或者被占用则插入磁盘中的文件
}
