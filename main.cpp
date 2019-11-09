#include "main.h"
#include <sstream>
#include <cstdio>
#include <ctime>
#include <pthread.h>
#include <sys/time.h>
std::string Main::path="./data/";
int Main::pid=1;
pthread_mutex_t Main::mutex=PTHREAD_MUTEX_INITIALIZER;

Main::Main():dt(DataTable::get_instance()),ds(new FileDS())
{
}

//打印菜单
void Main::Menu()
{
    std::cout<<"------------------------  Linux环境高级编程作业------------------------\n";
    std::cout<<"    1.从终端插入数据：insertfromterminal  \n ";
    std::cout<<"   2.从文件插入数据：insertfromfile\n";
    std::cout<<"    3.查找数据：select 属性(xxx) minimum(xxx) maximum(xxx)  (范围查找)\n";
    std::cout<<"    4.建立索引：createindex (建立索引)\n";
    std::cout<<"    5.多线程插入性能测试：mutiplethread\n";
    std::cout<<"    6.退出：exit\n    ";
    std::cout<<"                                                 by 金祝光 201922081133\n";
}


//获取用户指令
void Main::GetCommand()
{
    std::string command;
    std::cout<<"DataTable >";
    std::cin>>command;
    while(command!="exit")
    {
        OperatorOnTable(command);
        std::cout<<"DataTable >";
        std::cin>>command;
    }
    std::cout<<"再见！\n";
}


//对于数据表的操作
void Main::OperatorOnTable(std::string op)
{
    if(op=="insertfromterminal")
    {
        insert(new TerminalDS());
    }
    else if(op=="help")
    {
        Menu();
    }
    else if(op=="insertfromfile")
    {
        insert(new FileDS());
    }
    else if(op=="select")
    {
        
        search();
    }
    else if(op=="createindex")
    {
        create_index();   
    }
    else if(op=="mutiplethread")
    {
        mutiplethread();
    }
    else
    {
        std::cout<<"未定义的命令，请重新输入;或输入help获取帮助\n";
    }
}

//建立索引
void Main::create_index()
{
    dt->create_index();
}

//从文件插入
void Main::insert(DataSource* ds)
{
    dt->insert(ds->read());
}
/*
void Main::insert_from_terminal()
{

}*/

//查找数据
void Main::search()
{
    srand((int)time(0));
    int col=rand()%101;
    int minimum=rand()%1000;
    int maximum=rand()%1000+minimum;
    std::cout<<"在第"<<col<<"列上搜索；"<<"范围["<<minimum<<","<<maximum<<"]\n";
    dt->search(col,minimum,maximum);
}

//插入函数
void* Main::insert_to_file(void* filename)
{
    srand((int)(time(0)));
    int file_name=*((int*)filename);
    std::string file=path+std::to_string(file_name)+".txt";
    std::ofstream out(file);
    std::vector<std::string> datas;
    for(int i=0;i<1000;i++)
    {
        std::string line;
        line.clear();
        for(int j=0;j<100;j++)
        {
            line=line+std::to_string(rand()%100001)+" ";
        }
        out<<line<<"\n";
    }
    out.close();
    pthread_mutex_lock(&mutex);
    std::cout<<"thread "<<pid++<<"is finished!\n";
    pthread_mutex_unlock(&mutex);
    return NULL;
}

//多线程测试性能

void Main::mutiplethread()
{
    struct timeval start,end;
    gettimeofday(&start,NULL);
    pthread_t pids[1001];
    int filename[1001];
    for(int i=1;i<=1000;i++)
    {
        filename[i]=i;
    }
    for(int i=1;i<1001;i++)
    {
       pthread_create(&pids[i],NULL,insert_to_file,(void*)(&filename[i]));
       pthread_join(pids[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    gettimeofday(&end,NULL);
    long long usertime=(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    usertime/=1000*1000;
    std::cout<<"user time:"<<usertime<<std::endl;
}


