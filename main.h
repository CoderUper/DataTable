#include <iostream>
#include <memory>
#include <string>
#include "./DataSource/FileDS.h"
#include "./DataSource/TerminalDS.h"
#include "DataTable.h"
class Main{
public:
    Main();
    void Menu();
    void GetCommand();
    void OperatorOnTable(std::string);
    
private:
    void search();
    void insert();
    DataTable* dt;
    DataSource *ds;
};
