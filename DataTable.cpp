#include "DataTable.h"

DataTable::DataTable(uint _max_file_num,uint _max_file_data_rows,uint _data_rows):max_file_num(_max_file_num),max_file_data_rows(_max_file_data_rows),data_rows(_data_rows)
{
    pthread_mutex_init(&instance_mutex,NULL);

}
int DataTable::data_rows=0;

DataTable* DataTable::data_instance=NULL;
std::vector<int> DataTable::all_file;
std::map<int,std::fstream&> DataTable::recent_file;
