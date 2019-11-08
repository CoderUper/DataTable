#include "main.h"
Main::Main():dt(DataTable::get_instance()),ds(new FileDS())
{
}

//打印菜单
void Main::Menu()
{
    std::cout<<"------------------------  Linux环境高级编程作业------------------------\n";
    std::cout<<"    1.从终端插入数据：insert xxx,xxxx,xxxx,xxx,...  \n ";
    std::cout<<"    2.从文件插入数据：insert from file xxx.txt。\n";
    std::cout<<"    3.查找数据：select on 属性 where 属性>=xx and 属性<=xx(范围查找)\n";
    std::cout<<"    4.建立索引：craate index on 属性\n";
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
    else if(op.find("insert from file"))
    {
        insert();
    }
    else if(op.find("select"))
    {
        search();
    }
}

//从文件插入
void Main::insert()
{
    dt->insert(ds->read());
}

//查找数据
void search()
{
    dt->search();
}
