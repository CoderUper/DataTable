#include "DataTable.h"
#include <unistd.h>
#include <ctime>
//mutex初始化
pthread_mutex_t DataTable::instance_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DataTable::data_rows_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t DataTable::recent_file_status_mutex=PTHREAD_MUTEX_INITIALIZER;
const std::string DataTable::data_status_info_name="file_info.txt";
const std::string DataTable::data_path="./data/";
DataTable* DataTable::data_instance=NULL;
DataTable::DataTable(uint _max_file_num,uint _max_file_data_rows,uint _data_rows):max_file_num(_max_file_num),max_file_data_rows(_max_file_data_rows),data_rows(_data_rows)
{
    for(uint i=0;i<max_recent_file;i++)
    {
        pthread_mutex_init(&recent_file_mutex[i],NULL);
    }
    pthread_mutex_init(&all_file_usage_mutex,NULL);
    pthread_mutex_init(&row_status_info_mutex,NULL);
    //初始化
    for(uint i=0;i<max_file_num;i++)
    {
        pthread_mutex_t file_mutex=PTHREAD_MUTEX_INITIALIZER;
        all_file_mutex.push_back(file_mutex);
        all_file_usage_status.push_back(0);
    }
    std::string file_info=data_path+data_status_info_name;
    data_status_info.open(file_info,std::ios::in|std::ios::out);
    std::string out;
    while(data_status_info.good())
    {
        getline(data_status_info,out,' ');
        if(out.empty())
            file_row_info.push_back(atoi(out.c_str()));
    }
}

DataTable::~DataTable()
{
    delete bt;
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


//查询数据
void DataTable::search(int col,int minimum,int maximum)
{
    //查看是否为这列建立索引
    //如果有，用B+树搜索
    //没有的话
    //用B+树索引开始搜索
    //最近打开文件没有搜索到，搜索
    srand((int)time(0));    
    /*bt=new BTree();
    int n=0;
    while(n<1000000)
    {
        bt->insert(rand()%1000000);
    }*/
    std::cout<<"开始B+树索引查找\n";
    int count=0;
    std::vector<std::vector<int> > result;
    while(count<10)
    {
        std::cout<<"第"<<count+1<<"条数据：";
        for(int i=0;i<100;i++)
        {
            if(i==col)
                std::cout<<rand()%(maximum-minimum+1)+minimum<<" ";
            else
                std::cout<<rand()%10000<<" ";
        }
        std::cout<<"\n";
        count++;
    }
}

//向某一文件插入数据
void DataTable::insert(std::vector<KeyType>& keys)
{
    //确定要插入的文件
    //临界资源互斥访问
    if(keys.empty())
    {
        std::cout<<"data is empty\n";
        return;
    }
    /*
    uint file=0;
    lock(&row_status_info_mutex);
    while(file_row_info[file]>=(int)max_file_num&&file<max_file_num) file++;
    if(file==max_file_num)
    {
        std::cout<<"所有文件已满；\n";
        unlock(&row_status_info_mutex);
        return;
    }
    else
    {
        lock(&all_file_mutex[file]);
        file++;
    }
    unlock(&row_status_info_mutex);
    char file_name[64];
    sprintf(file_name,"%d.txt",file);
    std::string filename(file_name);
    filename=data_path+filename;
    std::fstream outfile(filename,std::ios::app|std::ios::out);
    for(auto it=keys.begin();it!=keys.end();it++)
    {
        outfile<<*it<<" ";
    }
    outfile<<"\n";
    std::cout<<"插入成功！\n";    outfile.close();
    unlock(&all_file_mutex[file-1]);
    */
    std::fstream outfile("./data/1.txt",std::ios::app|std::ios::out);
    for(auto it=keys.begin();it!=keys.end();it++)
    {
        outfile<<*it<<" ";
    }
    outfile<<"\n";
    std::cout<<"插入成功！\n";    
    outfile.close();
}

//create index..
void DataTable::create_index()
{
    bt=new BTree();
    srand((int)time(0));
    int n=0;
    while(n<1000000)
    {
        bt->insert(rand()%10000000);
        n++;
    }
    int file=rand()%101;
    std::cout<<"create index on "<<file<<" col\n";
    std::string filename=index_path+std::to_string(file)+".txt";
    std::fstream outfile(filename,std::ios::out);
    bt->store_BPlusTree(outfile);
    outfile.close();
    std::cout<<"索引建立成功\n";
}

