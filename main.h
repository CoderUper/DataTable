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
    void insert(DataSource *ds);
    void create_index();
    void mutiplethread();
    static void* insert_to_file(void* filename);
    DataTable* dt;
    DataSource *ds;
    static std::string path;
    static int pid;
    static pthread_mutex_t mutex;
};
