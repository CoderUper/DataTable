#include "main.h"
#include <sstream>
#include <cstdio>
#include <ctime>
Main::Main():dt(DataTable::get_instance()),ds(new FileDS())
{
}

//打印菜单
void Main::Menu()
{
    std::cout<<"------------------------  Linux环境高级编程作业------------------------\n";
    std::cout<<"    1.从终端插入数据：insert xxx,xxxx,xxxx,xxx,...  \n ";
    std::cout<<"    2.从文件插入数据：insert from file xxx.txt。\n";
    std::cout<<"    3.查找数据：select 属性(xxx) minimum(xxx) maximum(xxx)  (范围查找)\n";
    std::cout<<"    4.建立索引：createindex (建立索引)\n";
    std::cout<<"    5.多线程插入测试: multiple thread test\n";
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
    if(op=="insert")
    {
        insert();
    }
    else if(op=="help")
    {
        Menu();
    }
    else if(op=="insert from file")
    {
        insert();
    }
    else if(op=="select")
    {
        
        search();
    }
    else if(op=="createindex")
    {
        create_index();   
    }
}

//建立索引
void Main::create_index()
{
    dt->create_index();
}

//从文件插入
void Main::insert()
{
    dt->insert(ds->read());
}

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
