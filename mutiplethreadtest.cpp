#include <iostream>
#include <pthread.h>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sys/syscall.h>
using namespace std;
string path="./data/";
int pid=1;
pthread_mutex_t mutex;
void* insert_to_file(void* filename)
{
    srand((int)(time(0)));
    int file_name=*((int*)filename);
    string file=path+to_string(file_name)+".txt";
    ofstream out(file);
    vector<string> datas;
    for(int i=0;i<1000;i++)
    {
        string line;
        line.clear();
        for(int j=0;j<100;j++)
        {
            line=line+to_string(rand()%100001)+" ";
        }
        out<<line<<"\n";
    }
    out.close();
    pthread_mutex_lock(&mutex);
    cout<<"thread "<<pid++<<"is finished!\n";
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex,NULL);
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
    return 0;
}


