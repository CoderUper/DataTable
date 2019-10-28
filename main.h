#include <iostream>
#include <string>
//打印菜单
void Menu()
{
    std::cout<<"------------------------  Linux环境高级编程作业------------------------\n";
    std::cout<<"    1.插入数据：insert xxx,xxxx,xxxx,xxx,...  \n ";
    std::cout<<"    2.查找数据：select on 属性 where 属性>=xx and 属性<=xx(范围查找)\n";
    std::cout<<"    3.建立索引：craate index on 属性\n";
    std::cout<<"    4.退出：exit\n    ";
    std::cout<<"                                      by 金祝光 201922081133\n";
}


//获取用户指令
void GetCommand()
{
    std::string command;
    std::cout<<"DataTable >";
    std::cin>>command;
    while(command!="exit")
    {
        std::cout<<command<<std::endl;        
        std::cout<<"DataTable >";
        std::cin>>command;
    }
    std::cout<<"再见！\n";
}


//对指令进行解析
bool 
