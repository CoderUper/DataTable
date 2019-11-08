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
    void create_index();
    DataTable* dt;
    DataSource *ds;
};
